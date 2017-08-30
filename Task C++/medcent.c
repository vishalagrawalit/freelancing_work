//mid_cent.c file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "medcent.h"

#define MAX_STR_LEN 1000
#define MAX_PATIENT 100
#define MAX_DOCTOR 10
#define MAX_AILMENT 20
#define MAX_TREATMENT 10

int p, d, a, t;

struct patients{
    char *title;
    char *name;
    int age;
    char *gender;
    int ailment;
    int ailment_degree;
};

struct doctors{
    char *name;
    char *gender;
    int quality;
};

struct ailments{
    char *name;
    int ailment_determination;
    int ailment_treatment;
    int treatment;
};

struct treatments{
    char *name;
};

struct patients patients_record[MAX_PATIENT];
struct doctors doctors_record[MAX_DOCTOR];
struct ailments ailments_record[MAX_AILMENT];
struct treatments treatments_record[MAX_TREATMENT];

int open_patient_data_file()
{
    /* FileStream for the Patient File */
    FILE *patientFile;

    /* allocation of the buffer for every line in the File */
    char *buf = malloc(MAX_STR_LEN);
    char *tmp;

    /* if the space could not be allocated, return an error */
    if (buf == NULL) {
        printf ("No memory\n");
        return 1;
    }

    if ( ( patientFile = fopen( "Patients.txt", "r" ) ) == NULL ) //Reading a file
    {
        printf( "File could not be opened.\n" );
    }

    p = 0;
    while (fgets(buf, 999, patientFile) != NULL)
    {
        if ((strlen(buf)>0) && (buf[strlen (buf) - 1] == '\n'))
            buf[strlen (buf) - 1] = '\0';

        tmp = strtok(buf, ",");
        patients_record[p].title = (tmp);

        tmp = strtok(NULL, ",");
        patients_record[p].name = (tmp);

        tmp = strtok(NULL, ",");
        patients_record[p].age = atoi(tmp);

        tmp = strtok(NULL, ",");
        patients_record[p].gender =(tmp);

        tmp = strtok(NULL, ",");
        patients_record[p].ailment = atoi(tmp);

        tmp = strtok(NULL, ",");
        patients_record[p].ailment_degree = atoi(tmp);

        p++;
    }
    free(buf);
    fclose(patientFile);
    return 0;
}

int open_doctor_data_file()
{
    /* FileStream for the Doctor File */
    FILE *doctorFile;

    /* allocation of the buffer for every line in the File */
    char *buf = malloc(MAX_STR_LEN);
    char *tmp;

    /* if the space could not be allocated, return an error */
    if (buf == NULL) {
        printf ("No memory\n");
        return 1;
    }

    if ( ( doctorFile = fopen( "Doctors.txt", "r" ) ) == NULL ) //Reading a file
    {
        printf( "File could not be opened.\n" );
    }

    d = 0;
    while (fgets(buf, 999, doctorFile) != NULL)
    {
        if ((strlen(buf)>0) && (buf[strlen (buf) - 1] == '\n'))
            buf[strlen (buf) - 1] = '\0';

        tmp = strtok(NULL, ",");
        doctors_record[d].name = (tmp);

        tmp = strtok(NULL, ",");
        doctors_record[d].gender =(tmp);

        tmp = strtok(NULL, ",");
        doctors_record[d].quality = atoi(tmp);

        d++;
    }
    free(buf);
    fclose(doctorFile);
    return 0;
}

int open_ailment_data_file()
{
    /* FileStream for the Ailment File */
    FILE *ailmentFile;

    /* allocation of the buffer for every line in the File */
    char *buf = malloc(MAX_STR_LEN);
    char *tmp;

    /* if the space could not be allocated, return an error */
    if (buf == NULL) {
        printf ("No memory\n");
        return 1;
    }

    if ( ( ailmentFile = fopen( "Ailments.txt", "r" ) ) == NULL ) //Reading a file
    {
        printf( "File could not be opened.\n" );
    }

    a = 0;
    while (fgets(buf, 999, ailmentFile) != NULL)
    {
        if ((strlen(buf)>0) && (buf[strlen (buf) - 1] == '\n'))
            buf[strlen (buf) - 1] = '\0';

        tmp = strtok(NULL, ",");
        ailments_record[a].name = (tmp);

        tmp = strtok(NULL, ",");
        ailments_record[a].ailment_determination = atoi(tmp);

        tmp = strtok(NULL, ",");
        ailments_record[a].ailment_treatment = atoi(tmp);

        tmp = strtok(NULL, ",");
        ailments_record[a].treatment = atoi(tmp);

        a++;
    }
    free(buf);
    fclose(ailmentFile);
    return 0;
}

int open_treatment_data_file()
{
    /* FileStream for the Treatment File */
    FILE *treatmentFile;

    /* allocation of the buffer for every line in the File */
    char *buf = malloc(MAX_STR_LEN);
    char *tmp;

    /* if the space could not be allocated, return an error */
    if (buf == NULL) {
        printf ("No memory\n");
        return 1;
    }

    if ( ( treatmentFile = fopen( "Treatments.txt", "r" ) ) == NULL ) //Reading a file
    {
        printf( "File could not be opened.\n" );
    }

    t = 0;
    while (fgets(buf, 999, treatmentFile) != NULL)
    {
        if ((strlen(buf)>0) && (buf[strlen (buf) - 1] == '\n'))
            buf[strlen (buf) - 1] = '\0';

        tmp = strtok(NULL, ",");
        treatments_record[t].name = (tmp);

        t++;
    }
    free(buf);
    fclose(treatmentFile);
    return 0;
}

void print_results()
{
    //Traversing Patients
    int i, j;
    const char* available_doctor;
    for (i=0; i<p ; i++)
    {
        int maxi=-1, quality_doctor;
        //Doctor Seen
        for (j=0;j<d;j++)
        {
            if ((patients_record[i].gender==doctors_record[j].gender) && (maxi<=doctors_record[j].quality))
            {
                maxi = doctors_record[j].quality;
                available_doctor = doctors_record[j].name;
                quality_doctor = doctors_record[j].quality;
            }
        }

        //Ailment
        int ail = patients_record[i].ailment;

        //Treatment
        const char* the_treatment = treatments_record[ailments_record[i].treatment].name;

        //Success Algorithm

        //According to the Problem if the quality of doctor, ailment degree are high & ailment determination complexity is low then there
        //is a greater success rate.
        //As Ailment Determination Complexity must be low that's why we subtracted it from 100.
        int deter = ailments_record[ail-1].ailment_determination;
        int degree = patients_record[i].ailment_degree;

        double success = (degree)*(quality_doctor)*(100-deter);

        if (success/(100*100)>=50)
            printf("Patient: %s Doctor Seen: %s Ailment_Diagnosed: %s Treatment: %s Status: Successful\n", patients_record[i],
                   available_doctor,  ailments_record[ail-1].name, the_treatment);
        else
            printf("Patient: %s Doctor Seen: %s Ailment_Diagnosed: %s Treatment: %s Status: Un-Successful\n", patients_record[i],
                   available_doctor,  ailments_record[ail-1].name, the_treatment);
    }
}

