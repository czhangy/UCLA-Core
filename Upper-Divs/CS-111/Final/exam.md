# CS 111 Final (150 points)

## Question 1 (5 points)

Why would you try to never do 1024 `write` system calls (each writing 1 byte) versus a single `write` call writing 1024 bytes?

## Question 2 (5 points)

Consider the following code:

```c
#define NUM_THREADS 4

void* run(void*) {
    fork();
    printf("Hello\n");
}

int main() {
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; ++i) {
    	pthread_create(&threads[i], NULL, &run, NULL);
  	}
  	for (int i = 0; i < NUM_THREADS; ++i) {
    	pthread_join(threads[i], NULL);
  	}
 	return 0;
}

```

Assume there's an existing process that begins execution at `main`.



How many new processes are created when the original process exits?

## Question 3 (5 points)

Can one of the new processes become a zombie? If so, give an example.

## Question 4 (5 points)

Can one of the new processes become an orphan? If so, give an example.

## Question 5 (10 points)

How many times does `”Hello”` get printed? and most importantly, why does `”Hello”` get printed that many times?

## Question 6 (2 points)

Assume you have 4 × 8 TB hard disk drives, and you want to use RAID. Using this configuration, answer the following questions:



How much usable space would you have if you used RAID 0, how many drive failures could you recover from?

## Question 7 (2 points)

How much usable space would you have if you used RAID 1, how many drive failures could you recover from?

## Question 8 (2 points)

How much usable space would you have if you used RAID 5, how many drive failures could you recover from?

## Question 9 (2 points)

How much usable space would you have if you used RAID 6, how many drive failures could you recover from?

## Question 10 (2 points)

You want to use your RAID to be able to recover from disk failure. Besides space and how many failures you could recover from, what is one other factor you should consider when choosing a RAID configuration?

## Question 11 (1 point)

Consider a three level page table using the Sv39 format. That means each level of page tables uses 9 index bits, and there are 12 offset bits. Each PTE is 8 bytes, and physical addresses are 56 bits.



How large is a page?

## Question 12 (2 points)

Does each level of the page table fit on a page? Why?

## Question 13 (10 points)

Assume that virtual address `0x00404038FF` maps to physical address `0x1118FF`; explain how you'd use a three level page table to do this translation. For each level of the page table, give the indices you would use. For everything except the level 0 page table, you may assume the entry is an abstract page table. The virtual address in binary is `0b000_0000_0100_0000_0100_0000_0011_1000_1111_1111`.

## Question 14 (7 points)

One variation is to use a gigapage (which is 1 GB). The page tables still fit within the original page size. What modification would you have to make to resolve `0x00404038FF` as a gigapage?

## Question 15 (15 points)

You're tasked with implementing a bank account transfer that works with multiple threads. You create a bank account structure with a lock and an amount representing the dollar amount of the bank account. This bank makes no cents (get it?) and only tracks whole dollar amounts. You remember how Java implements monitors and write transfer to lock the entire function. Your initial implementation is as follows:

```c
struct bank_account {
  	pthread_mutex_t lock;
  	int amount;
};

void transfer(struct bank_account *this,
              int amount,
              struct bank_account *that) {
  	pthread_mutex_lock(&this->lock);
  	if (this->amount >= amount) {
    	this->amount -= amount;
    	that->amount += amount;
  	}
  	pthread_mutex_unlock(&this->lock);
}
```

Give an example of a data race that could occur. You may explain it using abstract bank accounts such as: bank account `A`, `B`, and `C`.

## Question 16 (15 points)

You change the code to the following:

```c
void transfer(struct bank_account *this,
              int amount,
              struct bank_account *that) {
  	pthread_mutex_lock(&this->lock);
  	pthread_mutex_lock(&that->lock);
  	if (this->amount >= amount) {
    	this->amount -= amount;
    	that->amount += amount;
  	}
  	pthread_mutex_unlock(&that->lock);
  	pthread_mutex_unlock(&this->lock);
}
```

Your code now does not have any data races, but can deadlock. What are two things you could do to prevent the deadlock? You do not have to write any code. Explain what you would do to implement each strategy (in different paragraphs please).

## Question 17 (10 points)

Someone suggests using two variables is wasteful, you can just use a semaphore that keeps track of the amount of money in each account. They provide the following implementation that has no data races:

## Question 18 (6 points)

In Lab 4, using a block size of 1024, you created a symbolic link (or soft link) to the name `hello-world`. Why were you able to store the content of the symbolic link within the inode itself? Explain why this optimization only works for names less than or equal to 60 bytes.

## Question 19 (7 points)

Regular files are allocated across a given number of blocks. The inode structure records the number of 512 byte blocks used and an explicit size record. Someone claims that you could just calculate the size using the number of 512 byte blocks. Explain why you need to explicitly record the size.

## Question 20 (7 points)

The inode (generally) points to the content of a file. Explain the condition(s) required for the kernel to delete an inode and free the blocks it points to.

## Question 21 (2 points)

Assume you have a buddy allocator that initially has a single 1024 byte free block. You receive an allocation of 120 bytes.



What is the size of the block used for the preceding allocation?

## Question 22 (3 points)

What are the sizes of the free blocks after the allocation and how many are there?

## Question 23 (2 points)

How many bytes are lost due to internal fragmentation for the 120 byte allocation

## Question 24 (2 points)

Assume you have a single 1024 byte free block again, and you receive 180 byte sized allocations.



How many TOTAL 180 byte allocations could a single 1024 byte free block hold?

## Question 25 (7 points)

What is the TOTAL amount of internal fragmentation for all your 180 byte allocations with the initial 1024 byte free block. Why is this amount of fragmentation acceptable?

## Question 26 (4 points)

Assume we only had 128 byte allocation, causing no internal or external fragmentation with the buddy allocator. Why would we still want to use a slab allocator for only 128 byte allocations?

## Question 27 (2 points)

Assume you're thinking about implementing a type 2 hypervisor. What CPU mode does the guest kernel execute in?

## Question 28 (8 points)

You're now tasked with implementing the type 2 hypervisor. The CPU you're implementing this for has few privileged (kernel) instructions, and no non-privileged (user) instructions behave differently in kernel mode. What is the best implementation strategy? Explain how it would work at a high level.

