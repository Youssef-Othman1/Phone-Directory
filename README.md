# Phone-Directory
Phone Directory implemented using C language. 
It creates and maintains the directory using console interface. 

Program functionalities:

1. LOAD (Read from file): This command reads in a file name and loads the phone directory from this file. The file is a text file that is comma delimited in which each entry is found on a separate line.
Each entry must contain the last name, first name, date of birth, street address, phone number and email. An example of one line in the file is as follows: Steven,Thomas,10-06-1995,26 Elhoreya Street,01234567899,sthomas@gmail.com

2. QUERY (Search): The system should process a request by the user to look up information about a specific entry. The user must supply the person’s last name, and the system should provide the first name, address, email and phone number for all users of that last name.

3. ADD: The system should prompt the user field by field for the data of a single record and add it to the directory with suitable validations.

4. DELETE: The user should be prompted for the name – last and first and all records associated with that name should be deleted from the directory.

5. MODIFY: The user should be prompted for a last name. Then the user should be prompted field by field to modify the information for one of the records (selected by user) that have that last name.

6. Print (Sort): Print the entire directory, in sorted order.
You should prompt the user to choose if sort should be done based on either last name or date of birth.

7. SAVE: Save the directory by writing it out to an external file in a format similar to that explained in the Load command.

8. QUIT: Exit (without saving the directory in the external file). You should display a warning to the user about all of his/her changes will be discarded.
