/* Task B2: Safe input, file-error handling, and argument validation.
   Try a long donor name, a missing file, and invalid command-line arguments. */
#include <stdio.h>
#include <string.h>
#include <errno.h>

int valid_group(const char *g) {
    const char *groups[]={"A+","A-","B+","B-","AB+","AB-","O+","O-"};
    for (int i=0;i<8;i++) if (strcmp(g,groups[i])==0) return 1;
    return 0;
}
int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1],"input")==0) {
        char name[32];
        printf("Enter donor name (max 31 characters): ");
        if (!fgets(name,sizeof name,stdin)) return 1;
        name[strcspn(name,"\n")]='\\0';
        if (strlen(name)==sizeof name-1) {
            int ch; while ((ch=getchar())!='\\n' && ch!=EOF) {}
            puts("Name may have been truncated; input remainder discarded.");
        }
        printf("Stored name: %s\n",name);
        return 0;
    }
    if (argc == 2 && strcmp(argv[1],"file")==0) {
        FILE *fp=fopen("missing_bloodbank_data.txt","r");
        if (!fp) { perror("missing_bloodbank_data.txt"); return 1; }
        fclose(fp); return 0;
    }
    if (argc == 3 && strcmp(argv[1],"find")==0) {
        if (!valid_group(argv[2])) { fprintf(stderr,"Invalid blood group: %s\n",argv[2]); return 2; }
        printf("Searching donors of group %s\n",argv[2]); return 0;
    }
    fprintf(stderr,"Usage: %s input | file | find GROUP\n",argv[0]);
    return 1;
}
