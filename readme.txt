To compile the program use:
        make st_pipeline

To run the program use:
        ./st_pipeline <random_numbers_to_generate> <random_seed>

* The random seed is not mandatory to provide.

chatGPT query:
can you generate code in c of thread safe queue with the following properties:
1. it has mutex protection
2. works in a multithreaded environment
3. object has ability to wait in queue without busy waiting
4. the queue will hold void*

