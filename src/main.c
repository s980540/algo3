#include "main.h"

#include "thread.h"
#include "nvme_mi.h"
#include "bin.h"

foo_ts foo = {.mutex = (PTHREAD_MUTEX_INITIALIZER), .val = 0};

thread_info_t *m_thread_info0;
thread_info_t *m_thread_info1;
thread_info_t *m_thread_info2;
thread_info_t *m_thread_info3;

int thread_init(int argc, char *argv[])
{
    m_thread_info0 = malloc(sizeof(thread_info_t));
    m_thread_info0->thread_id = 0;
    m_thread_info0->sleep_nsec = THREAD_SLEEP_MSEC(500);
    pthread_create(&m_thread_info0->thread, NULL, main_thread0, m_thread_info0);

    m_thread_info1 = malloc(sizeof(thread_info_t));
    m_thread_info1->thread_id = 1;
    m_thread_info1->sleep_nsec = THREAD_SLEEP_MSEC(10);
    pthread_create(&m_thread_info1->thread, NULL, main_thread1, m_thread_info1);

    m_thread_info2 = malloc(sizeof(thread_info_t));
    m_thread_info2->thread_id = 2;
    m_thread_info2->sleep_nsec = THREAD_SLEEP_MSEC(300);
    pthread_create(&m_thread_info2->thread, NULL, main_thread2, m_thread_info2);

    m_thread_info3 = malloc(sizeof(thread_info_t));
    m_thread_info3->thread_id = 3;
    m_thread_info3->sleep_nsec = THREAD_SLEEP_MSEC(500);
    pthread_create(&m_thread_info3->thread, NULL, main_thread3, m_thread_info3);

    pthread_join(m_thread_info0->thread, NULL);
    pthread_join(m_thread_info1->thread, NULL);
    pthread_join(m_thread_info2->thread, NULL);
    pthread_join(m_thread_info3->thread, NULL);

    return 0;
}

int thread_delete(void)
{
    free(m_thread_info0);
    free(m_thread_info1);
    free(m_thread_info2);
    free(m_thread_info3);

    return 0;
}

int thread_test(int argc, char *argv[])
{
    printf("thread\n");
    srand(time(NULL));

    thread_init(argc, argv);
    thread_delete();

    return 0;
}

int main(int argc, char *argv[])
{
    int ret = 0;
    // thread_test(argc, argv);
    // nvme_mi_test_checksum();

    ret = generate_random_binfile(argc, argv);
    if (ret) {
        printf("generate_random_binfile failed (%d)\n", ret);
    }

    return ret;
}
