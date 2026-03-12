**Possibility 1: Manage a pool of raw bytes**

	`struct MemControlBlock``{`
	`std::size_t size_;`
	`bool available_;`
	`};`

* The memory managed by the control block lies directly after it in memory and has size_t bytes.
* There is an initial memory control block that manages the entire pool, the other blocks are contained within the memory it manages.
* Other memory control blocks are created each time alloc is called.
* Each time alloc is called a linear search is done to find a block of suitable size.
* When a deallocation occurs another linear search is performed to fine the block and its proceeding block so that the size_t can be adjusted to include the freed bytes.

Disadvantages:
* Not time efficient

Advantages:
* Object size is relatively small

**Possibility 2: Manage a doubly linked list**
* Constant time deallocation through the pointers.
* Downside is there is overhead for the storing of two pointers for each block.
* Allocations still take linear time.

Small Object Allocator (4 Layered Approach)

	 Chunk
	   |
	   v
	Fixed Allocator
	   |
	   v
	 Small Object Allocator
	   |
	   v
	Small Object

**Chunk** 
* Bottom layer
* Contains and manages a chunk of memory containing fixed size blocks.
* Contains logic that allows allocation and deallocation of memory block.
* When there are no more available blocks allocation will fail by returning 0.

	`struct Chunk {`
	`void Init(std::size_t blockSize, unsigned char blocks);`
	`void* Allocate(std::size_t blockSize);`
	`void Deallocate(void* p, std::size_t blockSize);`
	`unsigned char* pData_;`
	`unsigned char firstAvailableBlock_, blocksAvailable_;`
	`};`

* firstAvailableBlock holds the index of the first block available in the chunk
* blocksAvailable is the number of blocks available in the chunk
* When allocate and deallocate are called a size is passed as it would waste space if the chunk stored a blockSize member.
* No constructor, destructor, assignment operator is defined as it would negatively impact efficiency.
* Since blocks can either be used or unused, all unused blocks contain an index of the next unused block in their first byte. This creates a singly linked list without using any extra memory.
* The singly linked list allows for constant time allocation and deallocation enabling a fast and efficient way to find available blocks.

	`void Chunk::Init(std::size_t blockSize, unsigned char blocks) {`
		`pData_ = new unsigned char[blockSize * blocks];`
		`firstAvailableBlock_ = 0;`
		`blocksAvailable_ = blocks;`
		`unsigned char i = 0;`
		`unsigned char* p = pData_;`
		`for (; i != blocks; p += blockSize)`
		`{`
		`*p = ++i;`
		`}`
	`}`

* Each chunk can only contain a max of 255 blocks of each 4 bytes. This is due to the fact that the singly linked list uses 1 byte for the index to the next block. This means the maximum index that it can represent is 255. The reason you can't use 2 bytes for the index is that the block size may only be 1/2 bytes since it's a small object allocator.

**FixedSizeAllocator**

	class FixedAllocator {
	...
	private:
	std::size_t blockSize_;
	unsigned char numBlocks_;
	typedef std::vector<Chunk> Chunks;
	Chunks chunks_;
	Chunk* allocChunk_;
	Chunk* deallocChunk_
	}

* Aggregates an array of chunks.
* For allocation it does not iterate through the chunks it holds an array to the last chunk that was used for allocation. If the chunk at the pointer is full then it preforms a linear search. This means its able to perform allocation in constant time with occasional slowdowns.
* When a allocation request comes through and all chunks are full it will add a new chunk to its pool.
* For deallocation it has to walk through each chunk and check if the pointer falls between the `PData` and `pData_ + blockSize_ * numBlocks_`.
* A potential solution to speed up lookups is to cache freed blocks. This however works badly with common strategies found when dealing with small objects.
	* Bulk allocation: Caching stores pointers that will not be used since no new allocations will come in, thus it wastes space and also uses up time.
	* Bulk deallocation in same order/in reverse order: When objects are bulk deallocated you have to clear the cache each time and you did not used it so there is time spent managing something that was not used at all.
	* Butterfly: This is random allocation and deallocation so in this case caching is useful.
* An alternative to caching is to store a pointer that points to the last chunk that was used for deallocation. When a deallocation occurs the chunk pointed to is checked first then if its the wrong chunk a linear search is performed starting from the pointer and moving both up the list and down the list with two iterators.
* If allocation bulk adds chunks then deallocation either hits right away or the next chunk is fetched.
* Another strategy to decrease cost is that a chunk is only freed when there are two empty chunks. This was there is no unnecessary allocations and deallocations of a chunk when a deallocation happens and a chunk is freed, and the next operation is an allocation a new chunk does not have to be created since the old chunk is still there.

**SmallObjectAllocator**

	class SmallObjAllocator {
	public:
	SmallObjAllocator(
	std::size_t chunkSize,
	std::size_t maxObjectSize);
	void* Allocate(std::size_t numBytes);
	void Deallocate(void* p, std::size_t size);
	private
	std::vector<FixedAllocator> pool_;
	};

* Chunk size defines the default size of a chunk
* maxObjectSize defines the largest size of objects that are considered small. IF a request for a new object larger than maxObjectSize comes in then it is forwarded to `::operator new`.
* The size parameter in Deallocate is required because searching all FixedAllocators to find the right one would be too expensive. Instead, the caller passes the size, making lookup trivial
* Initially, `pool_[i]` handles size `i` which leads to a constant time lookup but wastes memory because you allocate slots for every size up to `maxObjectSize`, even ones never used. Compiler padding makes this worse.
* A better apporach is to only store FixedAllocators for sizes actually requested. Pool_ stays small but requires a binary search for lookup. Counterintuitively, this can be _faster_ in practice because smaller memory usage means better CPU cache utilization.
* Two-pointer caching (`pLastAlloc_` and `pLastDealloc_`) sits on top of the binary search as a fast path. Since allocation and deallocation patterns tend to cluster around the same size repeatedly

**SmallObject**
* A wrapper class that overrides new and delete and passes the respective operations to SmallObjectAllocator.

