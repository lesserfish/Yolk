#pragma once

namespace Yolk
{
    namespace Memory
    {
        class MemoryIndexer
        {
            public:
            using Identifier = unsigned long long int;
            
            private:
            MemoryIndexer() : id(0) {}
            MemoryIndexer(const MemoryIndexer& cpy) = delete;
            MemoryIndexer(MemoryIndexer&&) = delete;
            MemoryIndexer& operator=(MemoryIndexer&&) = delete;
            MemoryIndexer& operator=(const MemoryIndexer&) = delete;
            public:
            static Identifier Tick()
            {
                static MemoryIndexer* Singleton = new MemoryIndexer();
                return Singleton->id++;
            }
            private:
            Identifier id;
        };
    }
}