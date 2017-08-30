#include<stdio.h>
//#include "medcent.h" //This is the header file contains the implementation of all the functionalities.
#include "medcent.c"

int main()
{
    //This will Read Patient data file into structure array "patient_records"
    open_patient_data_file();

    //This will Read Doctors data file into structure array "doctors_records"
    open_doctor_data_file();

    //This will Read Ailments data file into structure array "ailments_records"
    open_ailment_data_file();

    //This will Read Treatment data file into structure array "treatments_records"
    open_treatment_data_file();

    //This will print the summary of the MedCent.
    //The output has Patient Name, Doctor Seen, The Ailment Diagnosed, The Treatment & Whether the treatment is successful or not.

    //The treatment is considered as "Successful" when the success rate is >=50% otherwise it is "Un-Successful".

    print_results();

    return 0;
}
