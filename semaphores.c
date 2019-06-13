#include <unistd.h>
#include <stdio.h>

#define ODCZYT 0
#define ZAPIS 1
#define WORKERS 10

int semafor[2];

void LOCK()
{
  int x = 0;
  read(semafor[ODCZYT], &x, sizeof(x));
}

void UNLOCK()
{
  int x = 0;
  write(semafor[ZAPIS], &x, sizeof(x));
}

void INIT_SEMAPHORE(unsigned int a)
{
  for (int i = 0; i < a; i++)
    UNLOCK();
}

void worker(int id, int end_flag)
{
  int x = 0, i, j;
  printf("Worker %i startuje\n", id);

  LOCK();
  for (size_t i = 0; i < 4; i++)
  {
    printf("[%d]\n", id);
    fflush(stdout);
    sleep(3);
  }
  UNLOCK();

  printf("Worker %d kończy\n", id);
  write(end_flag, &x, sizeof(x));
}

int main()
{
  int end_flag[2], i, x;
  pipe(end_flag);
  pipe(semafor);
  INIT_SEMAPHORE(3);

  for (i = 0; i < WORKERS; i++)
  {
    if (!fork())
    {
      worker(i, end_flag[ZAPIS]);
      return 0;
    }
  }

  for (i = 0; i < WORKERS; i++)
  {
    read(end_flag[ODCZYT], &x, sizeof(x));
  }

  puts("Koniec programu.");
}
