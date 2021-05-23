# File Manager

This project is an implementation of Generic trees (N-ary trees) to create and store the hierarchies of files and folders. It also provides traversal, deletion, listing items within a directory/folder and, opening and saving of files.   

## Description

![image](https://user-images.githubusercontent.com/65674133/119253388-aae93780-bbce-11eb-86e9-9a5914e6ac46.png)

<div align="center">Implementation of Generic Tree using a Linked List</div>


##
Generic tree is a tree in which each node can have many children or nodes. Each sub-node is a folder or a file as specified by the user under one root node. To provide the traversal of the nodes according to the user, command line arguments are used. 

The nodes representing the folders are present only during the runtime. The hierarchy is presented as if it stored in a drive (virtual drive) but actually it is not stored in any drive. For the files, it gets stored in the memory in folder called that.dumps which is created (on the same folder where the FileManager.c file is saved in secondary memory of the user) during the runtime to store all the files created during the execution of the program irrespective of their presence in same or different directory/folder. All the files are dumped into that.dumps so it necessary to mention different filename for each file in other directories whereas same foldername can be repeated in other directories.

While making a file, an editor opens up to edit the file. Here I have used Notepad from Windows OS as an editor. Therefore, user can write text files and save it in the virtual directory. When the user comes out of the virtual drive, all files that were created in that.dumps during execution gets deleted to prepare that.dumps folder for a fresh start.

## Commands

### Make directory 
~~~
mkdir foldername
~~~
### Make file 
~~~
mkfile filename
~~~
### Change directory 
~~~
cd foldername
~~~
### Previous directory 
~~~
cd ..
~~~
### Open file 
~~~
open filename
~~~
### Remove directory 
~~~
remove foldername
~~~
### Remove file
~~~
remove filename
~~~
### Display a directory's files and subdirectories
~~~
ls -a
~~~
### Display tree of all folders and files 
~~~
ls -all
~~~

## Results

![2021-05-23 (2)](https://user-images.githubusercontent.com/65674133/119256818-1daede80-bbe0-11eb-92f4-bb0318ecf377.png)

![2021-05-23 (3)](https://user-images.githubusercontent.com/65674133/119256825-2c959100-bbe0-11eb-8346-2a9cc50db7be.png)

![2021-05-23 (4)](https://user-images.githubusercontent.com/65674133/119256826-2ef7eb00-bbe0-11eb-84cc-aa4932891c6e.png)

![2021-05-23 (5)](https://user-images.githubusercontent.com/65674133/119256827-2f908180-bbe0-11eb-961f-960b248fbfc8.png)

![2021-05-23 (6)](https://user-images.githubusercontent.com/65674133/119256828-30291800-bbe0-11eb-87d9-f87b1bf1142c.png)

![2021-05-23 (7)](https://user-images.githubusercontent.com/65674133/119256829-30291800-bbe0-11eb-8190-294a90618144.png)

![2021-05-23 (8)](https://user-images.githubusercontent.com/65674133/119256830-30c1ae80-bbe0-11eb-9f2e-979bd2a402eb.png)

![2021-05-23 (9)](https://user-images.githubusercontent.com/65674133/119256832-315a4500-bbe0-11eb-9172-b9d0039f2bc3.png)

![2021-05-23 (10)](https://user-images.githubusercontent.com/65674133/119256833-31f2db80-bbe0-11eb-82c1-96438f003e7b.png)

![2021-05-23 (11)](https://user-images.githubusercontent.com/65674133/119256834-31f2db80-bbe0-11eb-9951-1d9bc4df85ff.png)
