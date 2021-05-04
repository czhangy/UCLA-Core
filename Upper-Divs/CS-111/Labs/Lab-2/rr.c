#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

typedef uint32_t u32;
typedef int32_t i32;

struct process
{
  // Process info
  u32 pid;
  u32 arrival_time;
  u32 burst_time;
  // Establish pointers to insert inside the linked list
  TAILQ_ENTRY(process)
  pointers;
  // ----------------------------------------------------------------------------------
  // Track timing of individual processes
  u32 remaining_time;
  u32 waiting_time;
  u32 response_time;
  // ----------------------------------------------------------------------------------
};

// Defines container for list elements
TAILQ_HEAD(process_list, process);

u32 next_int(const char **data, const char *data_end)
{
  u32 current = 0;
  bool started = false;
  while (*data != data_end)
  {
    char c = **data;
    if (c < 0x30 || c > 0x39)
    {
      if (started)
        return current;
    }
    else
    {
      if (!started)
      {
        current = (c - 0x30);
        started = true;
      }
      else
      {
        current *= 10;
        current += (c - 0x30);
      }
    }
    ++(*data);
  }
  printf("Reached end of file while looking for another integer\n");
  exit(EINVAL);
}

u32 next_int_from_c_str(const char *data)
{
  char c;
  u32 i = 0;
  u32 current = 0;
  bool started = false;
  while ((c = data[i++]))
  {
    if (c < 0x30 || c > 0x39)
      exit(EINVAL);
    if (!started)
    {
      current = (c - 0x30);
      started = true;
    }
    else
    {
      current *= 10;
      current += (c - 0x30);
    }
  }
  return current;
}

void init_processes(const char *path,
                    struct process **process_data,
                    u32 *process_size)
{
  int fd = open(path, O_RDONLY);
  if (fd == -1)
  {
    int err = errno;
    perror("open");
    exit(err);
  }
  struct stat st;
  if (fstat(fd, &st) == -1)
  {
    int err = errno;
    perror("stat");
    exit(err);
  }
  u32 size = st.st_size;
  const char *data_start = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (data_start == MAP_FAILED)
  {
    int err = errno;
    perror("mmap");
    exit(err);
  }
  const char *data_end = data_start + size;
  const char *data = data_start;
  *process_size = next_int(&data, data_end);
  *process_data = calloc(sizeof(struct process), *process_size);
  if (*process_data == NULL)
  {
    int err = errno;
    perror("calloc");
    exit(err);
  }
  for (u32 i = 0; i < *process_size; ++i)
  {
    (*process_data)[i].pid = next_int(&data, data_end);
    (*process_data)[i].arrival_time = next_int(&data, data_end);
    (*process_data)[i].burst_time = next_int(&data, data_end);
  }
  munmap((void *)data, size);
  close(fd);
}

int main(int argc, char *argv[])
{
  // Check arg num
  if (argc != 3)
    return EINVAL;
  // List of all processes parsed from the processes.txt file
  struct process *data;
  u32 size;
  init_processes(argv[1], &data, &size);
  // Set quantum length
  u32 quantum_length = next_int_from_c_str(argv[2]);
  // Initialize the list container --> created using TAILQ_HEAD
  struct process_list list;
  TAILQ_INIT(&list);
  // Time tracking init
  u32 total_waiting_time = 0;
  u32 total_response_time = 0;
  // ----------------------------------------------------------------------------------
  u32 time = 0;
  bool finished = false;
  // Process tracking init
  struct process *cur, *ptr, *prev = NULL;
  // Initialize process times
  for (u32 i = 0; i < size; i++)
  {
    ptr = &data[i];
    ptr->response_time = -1;
    ptr->remaining_time = ptr->burst_time;
  }
  // Loop until all processes have been run
  while (!finished)
  {
    // Insert new processes to queue if arrival time reached
    for (u32 i = 0; i < size; i++)
    {
      ptr = &data[i];
      if (ptr->arrival_time == time)
        TAILQ_INSERT_TAIL(&list, ptr, pointers);
    }
    // Requeue
    if (prev)
    {
      TAILQ_INSERT_TAIL(&list, prev, pointers);
      prev = NULL;
    }
    // Schedule next process
    if (!TAILQ_EMPTY(&list))
    {
      // Get the first element in the queue
      cur = TAILQ_FIRST(&list);
      TAILQ_REMOVE(&list, cur, pointers);
      // Set response time if necessary
      if (cur->response_time == -1)
        cur->response_time = time - cur->arrival_time;
      for (u32 i = 0; i < quantum_length; i++)
      {
        // Increment time
        time++;
        // Decrement remaining time
        cur->remaining_time--;
        // Check if current process is done
        if (!cur->remaining_time || i == quantum_length - 1)
          break;
        else
          // Insert new processes to queue if arrival time reached
          for (u32 i = 0; i < size; i++)
          {
            ptr = &data[i];
            if (ptr->arrival_time == time)
              TAILQ_INSERT_TAIL(&list, ptr, pointers);
          }
      }
      // Requeue if necessary
      if (cur->remaining_time)
        prev = cur;
      // Calculate waiting time
      else
        cur->waiting_time = time - cur->arrival_time - cur->burst_time;
    }
    else
    {
      // Increment time in case of empty queue
      time++;
    }
    // Check if done
    finished = true;
    for (u32 i = 0; i < size; i++)
    {
      ptr = &data[i];
      if (ptr->remaining_time)
      {
        finished = false;
        break;
      }
    }
  }
  // Accumulate waiting and response times
  for (u32 i = 0; i < size; i++)
  {
    ptr = &data[i];
    total_response_time += ptr->response_time;
    total_waiting_time += ptr->waiting_time;
  }
  // ----------------------------------------------------------------------------------
  printf("Average waiting time: %.2f\n", (float)total_waiting_time / (float)size);
  printf("Average response time: %.2f\n", (float)total_response_time / (float)size);
  free(data);
  return 0;
}
