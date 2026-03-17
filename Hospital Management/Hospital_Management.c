#include<stdio.h>
#include<stdlib.h>

//STRUCTURE OF A DOCTOR

struct Doctor
{
	char name[30];
	char department[30];
	int id;
}dc;

//ADDING DOCTORS TO THE DATABASE

void add_doc()
{
	FILE *fptr;
	fptr = fopen("Records_doc.bin","ab");
	printf("Enter the name of the doctor: ");
	gets(dc.name);
	fflush(stdin);
	printf("Enter the Doctors ID: ");
	scanf("%d",&dc.id);
	fflush(stdin);
	printf("Enter the department: ");
	gets(dc.department);
	fwrite(&dc, sizeof(dc), 1, fptr);
	fclose(fptr);
}

//DISPLAYING DOCTORS DATA

void display_doc()
{
	FILE *fptr;
	fptr = fopen("Records_doc.bin","rb");
	if (fptr == NULL)
	{
		printf("No records available\n\n");
	}
	else
	{
		printf("__________________________________________________\n");
		printf("| %-5s | %-15s | %-20s |\n","ID","Name","Department");
		printf("|------------------------------------------------|\n");
		while(fread(&dc, sizeof(dc), 1, fptr))
		{
			printf("| %-5d | %-15s | %-20s |\n",dc.id, dc.name, dc.department);
		
		}
		printf("|------------------------------------------------|\n");
		printf("\n\n");
		fclose(fptr);
	}
}

//CHECKING AVAILABILITY OF A DOCTOR

int check(int iddc)
{
	FILE *fptr;
	
	fptr = fopen("Records_doc.bin","rb");
	while (fread(&dc, sizeof(dc), 1, fptr))
	{
		if (iddc == dc.id)
		{
			fclose(fptr);
			return 1;
		}
	}
	fclose(fptr);
	return 0;
}

//SEARCH A DOCTOR 

void search_doc()
{
	int iidc, iid, i;
	FILE *fptr;
	fptr = fopen("Records_doc.bin","rb");
	if (fptr == NULL)
	{
		printf("No records available\n\n");
		return;
	}
	else
	{
		printf("Enter the ID of the doctor you want to search: ");
		scanf("%d",&iid);
		i = iid;
		iid = check(iid);
		if (iid == 0)
			{
				printf("ID not found in the Records\n\n");
			}
		else
			{
				fptr = fopen("Records_doc.bin","rb");
				while (fread(&dc, sizeof(dc), 1, fptr))
				{
					if (i == dc.id)
					{
						printf("\nName = %s\nID = %d\nDepartment = %s\n\n",dc.name, dc.id, dc.department);
					}
				}
			}
	}
}

//DELETE A RECORD

void del_doc()
{
	FILE *fptr;
	FILE *tf;
	int i, a;
	fptr = fopen("Records_doc.bin","rb");
	if (fptr == NULL)
	{
		printf("No records available\n\n");
		return;
	}
	else
	{
		printf("Enter the ID you want to delete: ");
		scanf("%d",&i);
		a = i;
		i = check(i);
		if (i == 0)
		{
			printf("ID not found in the Records\n\n");
		}
		else
		{
			fptr = fopen("Records_doc.bin", "rb");
			tf = fopen("Temp_doc.bin", "wb");
			while (fread(&dc, sizeof(dc), 1, fptr))
			{
				if (a != dc.id)
				{
					fwrite(&dc, sizeof(dc), 1, tf);
				}
			}	
			fclose(fptr);
			fclose(tf);
		
			fptr = fopen("Records_doc.bin", "wb");
			tf = fopen("Temp_doc.bin", "rb");
			while (fread(&dc, sizeof(dc), 1, tf))
			{
				fwrite(&dc, sizeof(dc), 1, fptr);
			}
			printf("Record deleted successfully\n\n");
			fclose(tf);
			fclose(fptr);
		}
	}
}

//UPDATE A RECORD

void update_doc()
{
	FILE *fptr;
	FILE *tf;
	int i, a, b, ch;
	fptr = fopen("Records_doc.bin","rb");
	if (fptr == NULL)
	{
		printf("No records available\n\n");
		return;
	}
	else
	{
		printf("Enter the doctor's ID to update: ");
		scanf("%d",&a);
		b = a;
		a = check(a);
		if (a == 0)
		{
			printf("ID not found in the Records\n\n");
		}
		else
		{
			fptr = fopen("Records_doc.bin","rb");
			tf = fopen("Temp_doc.bin","wb");
			while (fread(&dc, sizeof(dc), 1, fptr))
			{
				if (b != dc.id)
				{
					fwrite(&dc, sizeof(dc), 1, tf);
				}
				else
				{
					printf("\t1.Change Name\n\t2.Change ID\n\t3.Change Department\n");
					printf("Enter the choice: ");
					scanf("%d",&ch);
					fflush(stdin);
					switch (ch)
					{
						case 1:
							{
								printf("Enter the new name of the Doctor: ");
								gets(dc.name);
							}
							break;
						
						case 2:
							{
								printf("Enter the new ID of the Doctor: ");
								scanf("%d",&dc.id);
								fflush(stdin);
							}
							break;
						
						case 3:
							{
								printf("Enter the new department of the Doctor:");
								gets(dc.department);
							}
							break;
						
						default:
							{
								printf("Invalid Input");
							}
							break;
					}
					fwrite(&dc, sizeof(dc), 1, tf);
				}
				fclose(tf);
				fclose(fptr);
			}
			fptr = fopen("Records_doc.bin","wb");
			tf = fopen("Temp_doc.bin","rb");
			while(fread(&dc, sizeof(dc), 1, tf))
			{
				fwrite(&dc, sizeof(dc), 1, fptr);
			}
			printf("Record updated successfully\n\n");
			fclose(tf);
			fclose(fptr);
		}
	}
}


//STRUCTURE OF A PATIENT 

struct Patient
{
	int id;
	char name[30];
	int age;
	char ass_doc[30];
	char phone_no[50];
	int day, month, year;
}pat;


//INSERT A NEW PATIENT

void add_pat()
{
	FILE *fptr;
	fptr = fopen("Records_pat.bin","ab");
	printf("Enter the name of the patient: ");
	gets(pat.name);
	fflush(stdin);
	printf("Enter the Patient ID: ");
	scanf("%d",&pat.id);
	printf("Enter the age of the patient: ");
	scanf("%d",&pat.age);
	printf("Enter the phone number of the patient: ");
	scanf("%s",&pat.phone_no);
	printf("Enter the date of admission dd-mm-yyyy: ");
	scanf("%d%d%d",&pat.day, &pat.month, &pat.year);
	fflush(stdin);
	printf("Enter the assigned doctor: ");
	gets(pat.ass_doc);
	fwrite(&pat, sizeof(pat), 1, fptr);
	fclose(fptr);
}

//DISPLAY PATIENT RECORD

void display_pat()
{
	FILE *fptr;
	fptr = fopen("Records_pat.bin","rb");
	if (fptr == NULL)
		{
			printf("No records are available\n\n");
		}
	else
	{
		printf("\n\n                            Patient's Details                                     \n");
		printf("_______________________________________________________________________________\n");
		printf("| %-15s | %-4s | %-04s | %-12s | %-08s | %-15s |\n","Name","ID","Age","Phone No.","Date of Adm","Assigned Doctor");
		printf("|------------------------------------------------------------------------------|\n");
		while (fread(&pat, sizeof(pat), 1, fptr))
		{
			printf("| %-15s | %-04d | %-04d | %-12s | %02d-%02d-%04d  | %-15s |\n", pat.name, pat.id ,pat.age, pat.phone_no, pat.day,pat.month,pat.year, pat.ass_doc);
		}
		printf("|______________________________________________________________________________|\n");
		printf("\n\n");
		fclose(fptr);
	}
}
//CHECK AVAILABILITY OF A PATIENT

int avl(int iddc)
{
	FILE *fptr;
	
	fptr = fopen("Records_pat.bin","rb");
	while (fread(&pat, sizeof(pat), 1, fptr))
	{
		if (iddc == pat.id)
		{
			fclose(fptr);
			return 1;
		}
	}
	fclose(fptr);
	return 0;
}

//SEARCH FOR A PATIENT

void search_pat()
{
	int iid, a;
	FILE *fptr;
	fptr = fopen("Records_pat.bin","rb");
	if (fptr == NULL)
	{
		printf("No records are available\n\n");
		return;
	}
	else
	{
		printf("Enter the ID of the patient you want to search: ");
		scanf("%d",&iid);
		a = iid;
		iid = avl(iid);
		if (iid == 0)
			{
				printf("ID not found in the Records\n\n");
			}
		else
			{
				fptr = fopen("Records_pat.bin","rb");
				while (fread(&pat, sizeof(pat), 1, fptr))
				{
					if (a == pat.id)
					{
					printf("\nPatient ID: %d\nName: %s\nAge :%d\nPhone No.: %s\nAssigned Doctor: %s\nDate of Admission: %d-%d-%d\n\n",pat.id, pat.name, pat.age, pat.phone_no, pat.ass_doc, pat.day,pat.month,pat.year);
					}
				}
			}
	}
}

//DELETE A PATIENT

void del_pat()
{
	FILE *fptr;
	FILE *tf;
	int i, a;
	fptr = fopen("Records_pat.bin","rb");
	if (fptr == NULL)
	{
		printf("No records are available\n\n");
		return;
	}
	else
	{
		printf("Enter the ID you want to delete: ");
		scanf("%d",&i);
		a = i;
		i = avl(i);
		if (i == 0)
		{
			printf("ID not available in the records\n\n");
		}
		else
		{
			fptr = fopen("Records_pat.bin","rb");
			tf = fopen("Temp_pat.bin","wb");
			while (fread(&pat, sizeof(pat), 1, fptr))
			{
				if (a != pat.id)
				{
					fwrite(&pat, sizeof(pat), 1, tf);
				}
			}
			fclose(fptr);
			fclose(tf);
		
			fptr = fopen("Records_pat.bin","wb");
			tf = fopen("Temp_pat.bin","rb");
			while(fread(&pat, sizeof(pat), 1, tf))
			{
				fwrite(&pat, sizeof(pat), 1, fptr);
			}
			fclose(fptr);
			fclose(tf);
			printf("Record deleted successfully\n\n");
		}	
	}
}

//UPDATING A PATIENT

void update_pat()
{
	FILE *fptr;
	FILE *tf;
	int a, b, ch;
	fptr = fopen("Records_pat.bin","rb");
	if (fptr == NULL)
	{
		printf("No records are available\n\n");
		return;
	}
	else
	{
		printf("Enter the patient ID to update: ");
		scanf("%d",&a);
		b = a;
		a = avl(a);
		if (a == 0)
		{
			printf("ID is not available in the records\n\n");
		}
		else
		{
			fptr = fopen("Records_pat.bin","rb");
			tf = fopen("Temp_pat.bin","wb");
			while (fread(&pat, sizeof(pat), 1, fptr))
			{
				if (b == pat.id)
				{
					printf("\t1.Change name\n\t2.Change ID\n\t3.Change Age\n\t4.Change Phone no\n\t5.Change date of addmission\n\t6.Change assigned doctor\n");
					printf("Enter the choice: ");
					scanf("%d",&ch);
					fflush(stdin);
					switch (ch)
					{
						case 1:
							{
								printf("Enter the new name: ");
								gets(pat.name);
							}
							break;
						
						case 2:
							{
								printf("Enter the new ID: ");
								scanf("%d",&pat.id);
							}
							break;
						
						case 3:
							{
								printf("Enter the new age: ");
								scanf("%d",&pat.age);
								fflush(stdin);
							}
							break;
						
						case 4:
							{
								printf("Enter the new phone no.: ");
								gets(pat.phone_no);
							}
							break;
						
						case 5:
							{
								printf("Enter the new date of addmission (dd-mm-yyyy): ");
								scanf("%d%d%d",&pat.day, &pat.month, &pat.year);
								fflush(stdin);
							}
							break;
						
						case 6:
							{
								printf("Enter the new assigned doctor: ");
								gets(pat.ass_doc);
							}
							break;
						
						default:
							{
								printf("Invalid Input");
							}
							break;
					}
					fwrite(&pat, sizeof(pat), 1, tf);
					fclose(fptr);
					fclose(tf);
				}
				else
				{
					fwrite(&pat, sizeof(pat), 1, fptr);
				}
			}
			fptr = fopen("Records_pat.bin","wb");
			tf = fopen("Temp_pat.bin","rb");
			while (fread(&pat, sizeof(pat), 1, tf))
			{
				fwrite(&pat, sizeof(pat), 1, fptr);
			}
			printf("Record updated successfully\n\n");
			fclose(tf);
			fclose(fptr);
		}
	}
}


main()
{
	int c1, c2, c3;
	while (1)
	{
		printf("\t__________________________________\n");
		printf("\t|   Hospital Management System    |\n");
		printf("\t|-------------------------------- |\n");
		printf("\t|          *Main Menu*            |\n");
		printf("\t|                                 |\n");
		printf("\t| 1. Access Doctor's Database     |\n");
		printf("\t| 2. Access Patient's Database    |\n");
		printf("\t|_________________________________|\n\n");
		printf("Enter the choice: ");
		scanf("%d",&c1);
		fflush(stdin);
		if (c1 == 1)
		{
			printf("\n");
			printf("\t_____________________________\n");
			printf("\t|      Doctor's Field        |\n");
			printf("\t|----------------------------|\n");
			printf("\t| 1. Insert new Doctor       |\n");
			printf("\t| 2. Display                 |\n");
			printf("\t| 3. Search                  |\n");
			printf("\t| 4. Delete a Record         |\n");
			printf("\t| 5. Update a Record         |\n");
			printf("\t| 6. Return to main menu     |\n");
			printf("\t|____________________________|\n\n");
			printf("Enter the choice: ");
			scanf("%d",&c2);
			fflush(stdin);
			switch (c2)
			{
				case 1:
					{
						add_doc();
					}
					break;
				
				case 2:
					{
						display_doc();
					}
					break;
					
				case 3:
					{
						search_doc();
					}
					break;
					
				case 4:
					{
						del_doc();
					}
					break;
					
				case 5:
					{
						update_doc();
					}
					break;
					
				case 6:
					continue;
					
				default:
					{
						printf("Invalid Input");
					}
					break;
			}
		}
		else if (c1 == 2)
		{
			printf("\n");
			printf("\t_____________________________\n");
			printf("\t|     Patient's Field        |\n");
			printf("\t|----------------------------|\n");
			printf("\t| 1. Insert new Patient      |\n");
			printf("\t| 2. Display                 |\n");
			printf("\t| 3. Search                  |\n");
			printf("\t| 4. Delete a Record         |\n");
			printf("\t| 5. Update a Record         |\n");
			printf("\t| 6. Return to main menu     |\n");
			printf("\t|____________________________|\n\n");
			printf("Enter the choice: ");
			scanf("%d",&c3);
			fflush(stdin);
			switch (c3)
			{
				case 1:
					{
						add_pat();
					}
					break;
					
				case 2:
					{
						display_pat();	
					}
					break;
					
				case 3:
					{
						search_pat();
					}
					break;
					
				case 4:
					{
						del_pat();
					}
					break;
					
				case 5:
					{
						update_pat();
					}
					break;
					
				case 6:
					continue;
					
				default:
					{
						printf("Invalid Input");
					}
					break;
			}
		}
	}
}
