/* TASK 1 - DATA DESIGN REVIEW: Patient register using nested structures */
#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define NAME_LEN 50
#define PHONE_LEN 16

typedef struct { int day, month, year; } Date;
typedef struct { int systolic, diastolic; } BloodPressure;

typedef struct {
    char name[NAME_LEN];
    int age;
    char phone[PHONE_LEN];       /* 10 digits plus room for '\0' */
    BloodPressure bp;
    Date visitDate;
} Patient;

static int patientCount = 0; /* private to this file */

int addPatient(Patient patients[], int capacity, const Patient *newPatient) {
    if (patients == NULL || newPatient == NULL || patientCount >= capacity)
        return 0;
    patients[patientCount++] = *newPatient;
    return 1;
}

void sortByAge(Patient patients[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (patients[j].age > patients[j + 1].age) {
                Patient temp = patients[j];
                patients[j] = patients[j + 1];
                patients[j + 1] = temp;
            }
}

void printPatient(const Patient *p) {
    printf("%-12s Age:%2d Phone:%s BP:%d/%d Visit:%02d/%02d/%04d\n",
           p->name, p->age, p->phone, p->bp.systolic, p->bp.diastolic,
           p->visitDate.day, p->visitDate.month, p->visitDate.year);
}

int main(void) {
    Patient patients[MAX_PATIENTS] = {0};
    Patient p1 = {"Anitha", 42, "9876543210", {120, 80}, {13, 10, 2026}};
    Patient p2 = {"Bala", 28, "9123456780", {118, 76}, {13, 10, 2026}};
    Patient p3 = {"Charan", 55, "9988776655", {135, 88}, {14, 10, 2026}};

    addPatient(patients, MAX_PATIENTS, &p1);
    addPatient(patients, MAX_PATIENTS, &p2);
    addPatient(patients, MAX_PATIENTS, &p3);

    puts("Patients sorted by age:");
    sortByAge(patients, patientCount);
    for (int i = 0; i < patientCount; i++) printPatient(&patients[i]);
    return 0;
}
