#include "object/block_allocator.h"


using namespace duck::object;


const int max_size = 8;

class A
{
public:
    int data_;
    int buff_[16];
};


int main(int argc, char* argv[])
{
    google::InstallFailureSignalHandler();
    google::InitGoogleLogging(argv[0]);


 
    FLAGS_stderrthreshold = 0;
    FLAGS_minloglevel = 0;


    BlockAllocator<A> allocator(4);

    A* buff[max_size] = {nullptr};

    int* head = allocator.head();
    printf("head: %08x\n", head[0]);
    printf("head: %08x\n", head[1]);

    for (int i = 0; i < max_size; i++)
    {
        buff[i] = allocator.allocate();
    }

    for (int i = 0; i < max_size; i++)
    {
        buff[i]->data_ = i;
        memset(buff[i]->buff_, 0, sizeof(buff[i]->buff_));
    }

    for (int i = 0; i < max_size; i++)
    {
        printf("%d: data_=%d\n", i, buff[i]->data_);
    }
    printf("head: %08x\n", head[0]);
    printf("head: %08x\n", head[1]);


    for (int i = 0; i < max_size; i++)
    {
        allocator.deallocate(buff[i]);
    }


    return 0;
}










