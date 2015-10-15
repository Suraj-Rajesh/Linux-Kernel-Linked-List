#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_LENGTH 30

typedef struct student
{
	char name[MAX_LENGTH];
	struct list_head list;
}student;

typedef struct lab
{
	char name[MAX_LENGTH];
	struct list_head list;
	struct list_head student_head;
}lab;

typedef struct department
{
	char name[MAX_LENGTH];
	struct list_head list;
	struct list_head lab_head;
}department;

void add_department(struct list_head * department_head)
{
	char string[MAX_LENGTH];
	memset(string, '\0', MAX_LENGTH);

	printf("\nADDING DEPARTMENT\n Enter the name of the department : ");
	fgets(string, MAX_LENGTH, stdin);
	if(string[strlen(string)-1] == '\n')
		string[strlen(string)-1] = '\0';
	else
		while(getchar()!='\n');
	
	department * dptr = (department *)malloc(sizeof(department));
	if (NULL == dptr)
	{
		printf("Memory allocation failure \n");
		return;
	} 
	strncpy(dptr->name, string, MAX_LENGTH);
	INIT_LIST_HEAD(&(dptr->list));
	INIT_LIST_HEAD(&(dptr->lab_head));
	list_add_tail(&(dptr->list), department_head);
}

struct list_head * find_lab_head(struct list_head * department_head)
{
	char string[MAX_LENGTH];
	memset(string, '\0', MAX_LENGTH);

	printf("Department name : ");
	fgets(string, MAX_LENGTH, stdin);
	if(string[strlen(string)-1] == '\n')
		string[strlen(string)-1] = '\0';
	else
		while(getchar()!='\n');

	struct list_head * iterate = NULL;
	department * dptr = NULL;
	list_for_each(iterate, department_head)
	{
		dptr = list_entry(iterate, department, list);
		if (0 == strcmp(string, dptr->name))
		{
			return &(dptr->lab_head);	
		}
	}
	printf("No such department exists \n");
	return NULL;
}

void add_lab(struct list_head * department_head)
{
	printf("\nADDING LAB\nEnter the department where you wish to add a lab \n");
	struct list_head * lab_head = NULL;
	lab_head = find_lab_head(department_head);
	if (NULL == lab_head)
	{
		return;
	}	
	
	char string[MAX_LENGTH];
	memset(string, '\0', MAX_LENGTH);

	printf("Enter the name of the lab : ");
	fgets(string, MAX_LENGTH, stdin);
	if(string[strlen(string)-1] == '\n')
		string[strlen(string)-1] = '\0';
	else
		while(getchar()!='\n');

	lab * lptr = (lab *)malloc(sizeof(lab));
	if (NULL == lptr)
	{
		printf("Memory allocation failure \n");
		return;
	} 
	strncpy(lptr->name, string, MAX_LENGTH);
	INIT_LIST_HEAD(&(lptr->list));
	INIT_LIST_HEAD(&(lptr->student_head));
	list_add_tail(&(lptr->list), lab_head);
}

struct list_head * find_student_head(struct list_head * department_head)
{
	char string[MAX_LENGTH];
	memset(string, '\0', MAX_LENGTH);
	struct list_head * lab_head = NULL;
	lab_head = find_lab_head(department_head);
	if (NULL == lab_head)
	{
		return NULL;
	}	

	printf("Lab name : ");
	fgets(string, MAX_LENGTH, stdin);
	if(string[strlen(string)-1] == '\n')
		string[strlen(string)-1] = '\0';
	else
		while(getchar()!='\n');
	struct list_head * iterate = NULL;
	lab * lptr = NULL;
	list_for_each(iterate, lab_head)
	{
		lptr = list_entry(iterate, lab, list);
		if (0 == strcmp(string, lptr->name))
		{
			return &(lptr->student_head);	
		}
	}
	printf("No such lab exists\n");
	return NULL;
}

void add_student(struct list_head * department_head)
{
	printf("\nADDING STUDENT\nEnter the department where you wish to add the student \n");
	struct list_head * student_head = NULL;
	student_head = find_student_head(department_head);
	if (NULL == student_head)
	{
		return;
	}	
	
	char string[MAX_LENGTH];
	memset(string, '\0', MAX_LENGTH);

	printf("Enter the name of the student : ");
	fgets(string, MAX_LENGTH, stdin);
	if(string[strlen(string)-1] == '\n')
		string[strlen(string)-1] = '\0';
	else
		while(getchar()!='\n');

	student * sptr = (student *)malloc(sizeof(student));
	if (NULL == sptr)
	{
		printf("Memory allocation failure \n");
		return;
	} 
	strncpy(sptr->name, string, MAX_LENGTH);
	INIT_LIST_HEAD(&(sptr->list));
	list_add_tail(&(sptr->list), student_head);
}

void display_labs(struct list_head * department_head)
{
	struct list_head * iterate = NULL;
	lab * lptr = NULL;
	printf("\nDISPLAYING LABS\nEnter the department whose labs you wish to display\n");
	struct list_head * lab_head = NULL;
	lab_head = find_lab_head(department_head);
	if (NULL == lab_head)
	{
		return;
	}
	list_for_each(iterate, lab_head)
	{
		lptr = list_entry(iterate, lab, list);
		printf("\n%s \n", lptr->name);
	}
}

void display_students(struct list_head * department_head)
{
	struct list_head * iterate = NULL;
	student * sptr = NULL;
	printf("\nDISPLAYING STUDENT\nEnter the department whose students you wish to display\n");
	struct list_head * student_head = NULL;
	student_head = find_student_head(department_head);
	if (NULL == student_head)
		return;
	list_for_each(iterate, student_head)
	{
		sptr = list_entry(iterate, student, list);
		printf("\n%s \n", sptr->name);
	}
}

void display_departments(struct list_head * department_head)
{
	struct list_head * iterate = NULL;
	department * dptr = NULL;
	printf("\nDISPLAYING DEPARTMENTS \n");
	list_for_each(iterate, department_head)
	{
		dptr = list_entry(iterate, department, list);
		printf("\n%s \n", dptr->name);
	}
	
}

void delete_student(struct list_head * department_head)
{
	struct list_head * iterate = NULL;
	student * sptr = NULL;
	printf("\nDELETING STUDENT\nEnter the department to which the student belongs to \n");
	struct list_head * student_head = NULL;
	student_head = find_student_head(department_head);
	if (NULL == student_head)
		return;
	
	char string[MAX_LENGTH];
	memset(string, '\0', MAX_LENGTH);

	printf("Enter the name of the student : ");
	fgets(string, MAX_LENGTH, stdin);
	if(string[strlen(string)-1] == '\n')
		string[strlen(string)-1] = '\0';
	else
		while(getchar()!='\n');

/*	list_for_each(iterate, student_head)
	{
		sptr = list_entry(iterate, student, list);
		if (0 == strcmp(sptr->name, string))
		{
			list_del(&(sptr->list));
			free(sptr);
			return;
		}
	}
*/


	student * pos, * temp;
	list_for_each_entry_safe(pos, temp, student_head, list)
	{
		if (0 == strcmp(pos->name, string))
		{
			list_del(&(pos->list));
			free(pos);
			return;
		}
	}
	printf("Student %s not found \n", string);
}

void delete_lab(struct list_head * department_head)
{
	char lab_name[MAX_LENGTH];
	char department_name[MAX_LENGTH];
	memset(lab_name, '\0', MAX_LENGTH);
	memset(department_name, '\0', MAX_LENGTH);
	printf("\nDELETING LAB\n Enter the department to which the lab belongs to \n");
	struct list_head * iterate = NULL;
	student * sptr = NULL;
	lab * lptr = NULL;
	struct list_head * s_head = NULL;
	struct list_head * l_head = NULL;
	printf("Department name : ");
	fgets(department_name, MAX_LENGTH, stdin);
	if(department_name[strlen(department_name)-1] == '\n')
		department_name[strlen(department_name)-1] = '\0';
	else
		while(getchar()!='\n');

	struct list_head * iterate_dept = NULL;
	department * idptr = NULL;
	list_for_each(iterate_dept, department_head)
	{
		idptr = list_entry(iterate_dept, department, list);
		if (0 == strcmp(department_name, idptr->name))
		{
			l_head = &(idptr->lab_head);	
		}
	}
	if (NULL == l_head)
	{
		printf("No such department exists \n");
		return;
	}

	printf("Lab name : ");
	fgets(lab_name, MAX_LENGTH, stdin);
	if(lab_name[strlen(lab_name)-1] == '\n')
		lab_name[strlen(lab_name)-1] = '\0';
	else
		while(getchar()!='\n');
	struct list_head * iterate_lab = NULL;
	lab * ilptr = NULL;
	list_for_each(iterate_lab, l_head)
	{
		ilptr = list_entry(iterate_lab, lab, list);
		if (0 == strcmp(lab_name, ilptr->name))
		{
			s_head = &(ilptr->student_head);	
		}
	}
	if (NULL == s_head)
	{
		printf("No such lab exists \n");
		return;
	}
	
	student * pos, *temp;
	list_for_each_entry_safe(pos, temp, s_head, list)
	{
		list_del(&(pos->list));
		free(pos);
	}
	iterate = NULL;

	lab * lab_pos, *lab_temp;
	list_for_each_entry_safe(lab_pos, lab_temp, l_head, list)
	{
		if (0 == strcmp(lab_pos->name, lab_name))
		{
			list_del(&(lab_pos->list));
			free(lab_pos);
		}
	}

}

void delete_department(struct list_head *department_head)
{
	printf("Enter the department to be deleted : ");
	char department_name[MAX_LENGTH];
	memset(department_name, '\0', MAX_LENGTH);
	fgets(department_name, MAX_LENGTH, stdin);
	if(department_name[strlen(department_name)-1] == '\n')
		department_name[strlen(department_name)-1] = '\0';
	else
		while(getchar()!='\n');
	
	department * pos = NULL;
	department * temp = NULL;
	lab * lab_pos = NULL;
	lab * lab_temp = NULL;
	student * student_pos = NULL;
	student * student_temp = NULL;
	struct list_head * lab_head = NULL;
	struct list_head * student_head = NULL;

	list_for_each_entry_safe(pos, temp, department_head, list)
	{
		if (0 == strcmp(pos->name, department_name))
		{
			lab_head = &(pos->lab_head);
			
			list_for_each_entry_safe(lab_pos, lab_temp, lab_head, list)
			{
				student_head = &(lab_pos->student_head);
				
				list_for_each_entry_safe(student_pos, student_temp, student_head, list)
				{
					list_del(&(student_pos->list));
					free(student_pos);
				}
				list_del(&(lab_pos->list));
				free(lab_pos);
			}
			list_del(&(pos->list));
			free(pos);
			return;
		}
	}
	printf("Department %s doesnt exist\n", department_name);
	return;
	
}
int main()
{
        char selection[10];
	int choice = 0;
	LIST_HEAD(department_head);

	while(1)
	{
		memset(selection, '\0', 10);
		printf("\n   MAKE YOUR CHOICE - ENTER THE APPROPRIATE INTEGER FOR THE DESIRED ACTION \n");
		printf("\n1. Add a department\n2. Add a lab\n3. Add a student\n4. Display departments\n5. Display Labs in a particular department\n6. Display list of students in a lab\n7. Delete a department\n8. Delete a lab\n9. Delete a student in a lab\n10. EXIT");
	printf("\n YOUR CHOICE : ");
	fgets(selection, 10, stdin);
	if (selection[strlen(selection)-1]=='\n')
		selection[strlen(selection)-1] = '\0';
	else
		while(getchar()!='\n');
	choice = atoi(selection);

	switch(choice)
	{
		case 1 : add_department(&department_head);
			 break;
		case 2 : add_lab(&department_head);
			 break;
		case 3 : add_student(&department_head);
			 break;
		case 4 : display_departments(&department_head);
                         break;
		case 5 : display_labs(&department_head);
                         break;
		case 6 : display_students(&department_head);
                         break;
                case 7 : delete_department(&department_head);
                         break; 
                case 8 : delete_lab(&department_head);
                         break; 
                case 9 : delete_student(&department_head);
                         break;
                case 10 : exit(0);
		default : printf("\nInvalid choice : Pls select proper choice (integer value)\n\n");
                          break; 
	}
	}
	return 0;
}


























