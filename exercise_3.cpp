#include <stdio.h>

/*
Write a program that asks number of students and creates an array of that many integers.
Program then initializes the array elements to -1.
Then the program asks user to enter student number in range 1 – nr of students or zero to stop. If
valid non zero number is given the program asks user to enter grade in the range 0-5 or -1 to not
enter a grade for the student.
When user stops by entering 0 then program prints student numbers followed by grade or N/A if
grade is -1.
*/

int main(void)
{
    int number_of_students;

    printf("Enter number of students:\n ");
    scanf("%d", &number_of_students);

    int grades[number_of_students];

    for (int i = 0; i < number_of_students; i++)
    {
        grades[i] = -1;
    }

    int student_number = -1;

    while (student_number != 0)
    {
        printf("Enter a student number:\n");
        scanf("%d", &student_number);
        if (student_number == 0)
        {
            printf("Grades will be printed next.\n");
        }
        else if (student_number < 1 || student_number > number_of_students)
        {
            printf("Not a valid student number. Try again\n");
        }
        else
        {
            int grade;
            printf("Enter student number %d (Valid grades 0-5. Type -1 if no grade was assigned)\n:", student_number);
            scanf("%d", &grade);
            if ((0 <= grade && grade <= 5) || grade == -1)
            {
                grades[student_number-1] = grade;
                printf("Grade %d is stored for student number %d\n", grade, student_number);
            }
            else
            {
                printf("Not a valid grade. Try again\n");
            }

        }

    }
    printf("%-10s %-5s\n", "Student", "Grade");
    for (int i = 0; i < number_of_students; i++) {
        if (grades[i] == -1) {
            printf("%-10d %-5s\n", i+1, "N/A");
        } else {
            printf("%-10d %-5d\n", i+1, grades[i]);
        }
    }


    return 0;
}

