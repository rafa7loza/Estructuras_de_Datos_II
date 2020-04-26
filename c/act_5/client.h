#include "constants.h"
#include "helper.h"

struct Client{
  char last_name_a[BUF_SIZE];
  char last_name_b[BUF_SIZE];
  char name[BUF_SIZE];
  char address[BUF_SIZE];
  char phone[PHONE];
  char age[AGE];
  char schedule[SCHEDULE];  // HH:MM
  char date[DATE];          // dd/mm/yyyy
};

void fill_client(struct Client * cl);
