#pragma once

#include <string>
#include <cstring>
#include <iostream>
#include <iomanip> 
#include <typeinfo>

#include <glog/logging.h>

#include "object/allocator.h"

namespace duck {
namespace object {

template<typename T>
class BlockAllocator : public Allocator<T>
{
public:
    BlockAllocator(int chunk_per_block) : chunk_per_block_(chunk_per_block), head_(nullptr) {
        head_ = allocate_block(sizeof(T));
    }

    T* allocate() {

        if (head_ == nullptr) {
            head_ = allocate_block(sizeof(T));

            
        }
        T* p = reinterpret_cast<T*>(head_);
        head_ = head_->next;

        printf("allocate: head=%p, next=%p\n", p, head_);
        return p;
    }

    void deallocate(T* p) {
        printf("deallocate: p=%p, head=%p\n", p, head_);
        Chunk* chunk = reinterpret_cast<Chunk*>(p);
        chunk->next = head_;
        head_ = chunk;

        
    }
    
    int* head() {
        return reinterpret_cast<int*>(head_);
    }

private:
    struct Chunk {
        Chunk *next;
    };

    Chunk* allocate_block(size_t chunk_size) {

        size_t block_size = chunk_per_block_ * chunk_size;
        printf("chunk_size=%d, chunk_per_block_=%d, block_size=%d\n", chunk_size, chunk_per_block_, block_size);
        Chunk* head = reinterpret_cast<Chunk*>(malloc(block_size));
        printf("head=%p\n", head);
        Chunk* chunk = head;
        for (int i = 0; i < chunk_per_block_ - 1; i++) {
            chunk->next = reinterpret_cast<Chunk*>(reinterpret_cast<char*>(chunk) + chunk_size);
            printf("next=%p\n", chunk->next);
            chunk = chunk->next;
        }        
        chunk->next = nullptr;


        int* ptr = reinterpret_cast<int*>(head);
        for (int i = 0; i < block_size / 4; i++) {
            printf("%02d: %08x\n", i, ptr[i]);

        }
        printf("\n");

        return head;
    }

protected:
    int chunk_per_block_;
    Chunk* head_;
};

}//namespace object
}//namespace duck









