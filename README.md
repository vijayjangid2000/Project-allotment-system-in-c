# Project-allotment-system-in-c
C Project. Project Allotment System.

Login:

1. Take username and password
2. Get employee details
3. Show menu accordingly

Allocation

1. Check for num of employees needed
2. Check for experienced employees
3. Check for domain expert
4. Assign first to employees who are involved in lesser projects
5. 1 product owner, 1 tech lead, 30% will be BA, 30% will be tester, 40% developer
6. Increase the value of involved project by 1, those who are selected
7. Change Project status from Idle to inProgress
8. Add the employees to manager Table.
9. Print employees selected.
10. Finished

Add Employee:

1. Take input from user
2. Create a local structure
3. Save that structure in the array
4. Update the employee file
5. Save the password and other details to loginFile (if employee is admin or manager)

Add Project:

1. Same as add employee
2. Difference is take client details also.

Files updated: Project, Client File.

User Flow:

1. Once user login, it return who is loging in, then we show options
2. Shows managers or admin options

Reports: 
1. Employees in project (by status, Idle, busy)
2. Projects (Idle, inProgress or Completed)
