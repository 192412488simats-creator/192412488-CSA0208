/* Task B4: Growable donor list, next-week eligibility report, memory cleanup.
   Input file donors.txt format: ID|Name|Group|Age|DD|MM|YYYY
   If absent, a small sample file is created for demonstration. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct { int id, age, day, month, year; char name[50], group[4]; } Donor;
typedef struct { Donor *data; size_t size, capacity; } DonorList;

int add_donor(DonorList *list, const Donor *d) {
    if(list->size==list->capacity) {
        size_t cap=list->capacity==0?2:list->capacity*2;
        Donor *p=realloc(list->data,cap*sizeof *p);
        if(!p) return 0;
        list->data=p; list->capacity=cap;
    }
    list->data[list->size++]=*d; return 1;
}
int load_donors(DonorList *list,const char *filename) {
    FILE *fp=fopen(filename,"r");
    if(!fp) {
        perror(filename);
        return 0;
    }
    char line[256];
    while(fgets(line,sizeof line,fp)) {
        Donor d;
        if(sscanf(line,"%d|%49[^|]|%3[^|]|%d|%d|%d|%d",
                  &d.id,d.name,d.group,&d.age,&d.day,&d.month,&d.year)==7) {
            if(!add_donor(list,&d)){perror("realloc");fclose(fp);return 0;}
        }
    }
    fclose(fp); return 1;
}
int day_number(int d,int m,int y){return y*365+m*30+d;}
int main(void) {
    DonorList list={NULL,0,0};
    if(!load_donors(&list,"donors.txt")) {
        puts("Create donors.txt using the format shown in the source comment, then rerun.");
        free(list.data); return 1;
    }
    printf("Loaded %zu donors; allocated capacity=%zu; donor-array memory=%zu bytes\n",
           list.size,list.capacity,list.capacity*sizeof(Donor));
    time_t now=time(NULL); struct tm *t=localtime(&now);
    int today=day_number(t->tm_mday,t->tm_mon+1,t->tm_year+1900);
    int count=0;
    for(size_t i=0;i<list.size;i++) {
        int last=day_number(list.data[i].day,list.data[i].month,list.data[i].year);
        int days=today-last;
        /* Example policy: 90-day interval; report donors who become eligible
           within the next 7 days (days 83 through 90). */
        if(days>=83 && days<90) {
            printf("Upcoming eligible: %d %s (%s), age %d\n",
                   list.data[i].id,list.data[i].name,list.data[i].group,list.data[i].age);
            count++;
        }
    }
    printf("Upcoming eligible donor count: %d\n",count);
    free(list.data); list.data=NULL; list.size=list.capacity=0;
    puts("Allocated donor memory released.");
    return 0;
}
