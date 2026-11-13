/* Task B3: Compare text and binary donor storage and update binary stock in place.
   Run with a record count argument, e.g. ./b3 10000 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct { int id; char name[32]; char group[4]; int age; } Donor;
typedef struct { int group_code, units; } Stock;

int update_units(FILE *fp, int index, int units) {
    Stock s;
    if (index < 0 || units < 0) return 0;
    if (fseek(fp,(long)index*(long)sizeof s,SEEK_SET)!=0) return 0;
    if (fread(&s,sizeof s,1,fp)!=1) return 0;
    s.units=units;
    if (fseek(fp,-(long)sizeof s,SEEK_CUR)!=0) return 0;
    return fwrite(&s,sizeof s,1,fp)==1;
}
int main(int argc,char *argv[]) {
    int n = argc>1 ? atoi(argv[1]) : 10000;
    if (n<1 || n>1000000) { puts("Choose 1 to 1000000 records"); return 1; }
    FILE *txt=fopen("donors_benchmark.txt","w+");
    FILE *bin=fopen("donors_benchmark.dat","w+b");
    if(!txt||!bin){perror("open"); if(txt)fclose(txt); if(bin)fclose(bin); return 1;}
    clock_t start=clock();
    for(int i=0;i<n;i++) fprintf(txt,"%d|Donor_%d|O+|%d\n",100000+i,i,18+i%50);
    double tw=(double)(clock()-start)/CLOCKS_PER_SEC;
    start=clock();
    for(int i=0;i<n;i++){Donor d={100000+i,"Sample Donor","O+",18+i%50}; if(fwrite(&d,sizeof d,1,bin)!=1){perror("write");return 1;}}
    double bw=(double)(clock()-start)/CLOCKS_PER_SEC;
    fflush(txt); fflush(bin);
    fseek(txt,0,SEEK_END); long ts=ftell(txt);
    fseek(bin,0,SEEK_END); long bs=ftell(bin);
    printf("Records: %d\nText bytes=%ld write_time=%.6f s\nBinary bytes=%ld write_time=%.6f s\n",n,ts,tw,bs,bw);
    rewind(txt); char line[128]; int tc=0; while(fgets(line,sizeof line,txt))tc++;
    rewind(bin); Donor d; int bc=0; while(fread(&d,sizeof d,1,bin)==1)bc++;
    printf("Read-back counts: text=%d binary=%d\n",tc,bc);
    if(n>=50000) {
        start=clock(); int ok=update_units(bin,49999,77);
        printf("Binary update of record 50000: %s, time=%.6f s\n",ok?"success":"failed",(double)(clock()-start)/CLOCKS_PER_SEC);
    } else puts("Use at least 50000 records to time record 50000 update.");
    fclose(txt); fclose(bin);
    return 0;
}
