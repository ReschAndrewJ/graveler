
#include <random>
#include <stdio.h>
#include <chrono>
#include <thread>


const unsigned max_rolls = 1'000'000'000;
const unsigned num_threads = 8; // my laptop only has 8 logical cores
const unsigned batch_size = max_rolls / num_threads;

std::thread threads[num_threads] = {};
unsigned maxOnes_arr[num_threads] = {};

void batch(unsigned thread_index) {
    unsigned maxOnes = 0;

    std::random_device rd; // each thread gets its own randomizer
    std::uniform_int_distribution distribution;

    for (unsigned roll = 0; roll < batch_size; ++roll) { // removed early escape

        unsigned count = 0;
        for (unsigned i=0; i<231; ++i) {
            unsigned item = distribution(rd) % 4; // 0 = item1, 1 = item2, 2 = item3, 3=item4
            count += item == 0;         // only item1 matters
        }
        maxOnes = (count >= maxOnes) ? count : maxOnes;
    }
    maxOnes_arr[thread_index] = maxOnes;
}

int main() {

    auto start = std::chrono::steady_clock::now(); 

    for (unsigned i=0; i<num_threads; ++i) threads[i] = std::thread(batch, i);
    for (unsigned i=0; i<num_threads; ++i) threads[i].join(); 

    unsigned maxOnes = maxOnes_arr[0];
    for (unsigned i=1; i<num_threads; ++i)  {
        unsigned m = maxOnes_arr[i];
        maxOnes = (m >= maxOnes) ?  m : maxOnes;
    }

    auto end = std::chrono::steady_clock::now(); 
    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    printf("Highest Ones Roll: %d\n", maxOnes);
    printf("Time to Run: %d milliseconds ( %0.3f seconds ) (%0.3f minutes)\n", 
        duration.count(), duration.count() / 1000.f, duration.count() / 1000.f / 60.f);

}