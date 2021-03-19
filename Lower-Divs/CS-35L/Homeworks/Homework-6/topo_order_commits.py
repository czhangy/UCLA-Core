import os, sys, zlib

# Task #1 - Find .git directory
git_dir = os.getcwd() # Get the current working directory
target = ".git"

while True:
    files = os.listdir(git_dir) # get all files in current dir
    parent = os.path.dirname(git_dir) # get parent dir, will return '/' if in root
    if target in files: # .git found in current directory
        break
    elif git_dir == parent: # root directory reached, no .git file found
        sys.stderr.write("Not inside a Git repository")
        sys.exit(1)
    else:
        git_dir = parent # iterate forward

# Task #2 - List branches
def get_files(dir_name):
    file_list = os.listdir(dir_name)
    all_files = list()
    for files in file_list:
        path = os.path.join(dir_name, files) # get the working path
        if os.path.isdir(path):
            all_files = all_files + get_files(path) # recursive search through subdirectories
        else:
            all_files.append(path)
    return all_files
    
branches = get_files(git_dir + '/.git/refs/heads') # extract important part of branches
for i in range(0, len(branches)):
    branches[i] = branches[i][branches[i].find('/.git/refs/heads/') + 17:]
branches.sort() # sort lexicographically for final output

# Task #3 - Build the commit graph
class CommitNode: # given class definition
    def __init__(self, commit_hash):
        # :type commit_hash:str
        self.commit_hash = commit_hash
        self.parents = set()
        self.children = set()
        self.parents2 = set() # help for task #5
        self.children2 = set()

nodes = dict()
roots = dict()
root_commits = list()

def build_DAG(current, child, git_dir, nodes, root_commits): # parent and child passed in as hashes, git_dir is string
    if current in nodes:
        return
    c = CommitNode(current) # build CommitNode for parent
    if (child is None):
        root_commits.append(c)
    else: # build children if not a root node
        c.children.add(child)
        c.children2.add(child)
    nodes[current] = c # insert into dictionary mapping hashes to nodes

    f = open(git_dir + '/.git/objects/' + current[:2] + '/' + current[2:40], 'rb') # get decompressed information
    contents = zlib.decompress(f.read())
    f.close()

    i = 0
    while (contents.find(b'parent', i) != -1): # build child --> parent link from c
        parent_hash = contents[contents.find(b'parent', i) + 7 : contents.find(b'parent', i) + 48]
        c.parents.add(parent_hash.decode('ascii'))
        c.parents2.add(parent_hash.decode('ascii'))
        i = contents.find(b'parent', i) + 48 # increment i to prevent repeated parents

    for node in c.parents: # recursive call / build parent --> child link to c
        discovered = False
        discovered_node = None
        if node in nodes:
            discovered = True
            discovered_node = nodes[node]
        if not discovered:
            build_DAG(node, current, git_dir, nodes, root_commits)
        else: # update previously discovered node
            discovered_node.children.add(current)
            discovered_node.children2.add(current)

for branch in branches:
    f = open(git_dir + '/.git/refs/heads/' + branch, 'r') # process leaf node
    hash_val = f.read()
    f.close()
    if hash_val not in roots: # create new key-value pair if neccessary
        roots[hash_val] = list()
    roots[hash_val].append(branch) # map root hash to branch name
    build_DAG(hash_val, None, git_dir, nodes, root_commits) # begin recursion

# Task #4 - Generate a topological ordering
topo_order = list() # initialize

def topo_sort(current, nodes, topo_order):
    if (current.children): # if the current node still has unprocessed children, exit
        return

    topo_order.append(current) # add current node into topo_order

    if not current.parents: # if current node is a root node, there's no more to process
        return

    current.parents.clear() # child -X-> parent

    for parents in current.parents2: # parent -X-> child
        nodes[parents].children.remove(current.commit_hash)
        if not nodes[parents].children: # recursive call
            topo_sort(nodes[parents], nodes, topo_order)


for node in root_commits: # find a leaf node
    topo_sort(node, nodes, topo_order) # fills topo_order

# Task #5 - Print the topological ordering with sticky ends

sticky = False

for i in range(0, len(topo_order)):
    current = topo_order[i].commit_hash[:-1]
    if (topo_order[i].commit_hash in roots): # get branch names
        for names in roots[topo_order[i].commit_hash]:
            current += " " + names
    if sticky: # get sticky start
        sticky_start = ""
        for hash_val in topo_order[i].children2:
            sticky_start += hash_val[:-1] + " "
        print("=" + sticky_start[:-1]) # print all children of current node first
        print(current) # print current node
        sticky = False
    elif (i < len(topo_order) - 1 and (topo_order[i + 1].commit_hash not in topo_order[i].parents2)): # get sticky end
        print(current)
        sticky_end = ""
        for hash_val in topo_order[i].parents2: # print all parents of current node
            sticky_end += hash_val[:-1] + " "
        print(sticky_end[:-1] + "=\n") # extra formatting
        sticky = True
    else: # normal case
        print(current)

