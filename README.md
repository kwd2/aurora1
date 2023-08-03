# aurora1
graph analysis of City of Aurora, IL expenditure reports

This analysis package is an example of a "graph" analysis.   This graph analysis method is widely applicable to many large data sets and allows for detailed analysis of such data sets.   The method is iterative and proceeds in a stepwise fashin, based on the results of previous iteration(s).


This analysis will be based on the following PDF data:

![image](https://github.com/kwd2/aurora1/assets/15908030/aab83661-c799-42ca-9de7-9deae0442e72)

The first page of each PDF contains header information and then every subsequent page has the same output format, such as:

![image](https://github.com/kwd2/aurora1/assets/15908030/0bb5262b-36b5-43a9-9891-b05f1463c601)

The individual files are downloaded to a directory and then converted to a text file

![image](https://github.com/kwd2/aurora1/assets/15908030/e6b6db0d-ccfd-4c7d-b475-b976cec5de05)


The text file can be opened in an editor.    Every section begins with the same format below.

![image](https://github.com/kwd2/aurora1/assets/15908030/d4e14af4-cf77-440b-9719-8e5b22903a19)

There are 262 seperate sections in the file being examined below

![image](https://github.com/kwd2/aurora1/assets/15908030/700fe598-a9fa-4407-a2bb-29cb9bce9ae6)

The data is given sperated into nine distinct "EAL DESCRIPTIONS" sections

![image](https://github.com/kwd2/aurora1/assets/15908030/8e559b9e-96b7-4613-bbe2-2df790f867ea)

The data is read with the code below and each time the "DEPT" line changes, the data for the previous block is printied out.


![image](https://github.com/kwd2/aurora1/assets/15908030/157c0b95-caec-4c42-9602-b60d13a0ab72)

The DEPARTMENT TOTAL dollar amounts are converted to integers for building the graph

![image](https://github.com/kwd2/aurora1/assets/15908030/5827a9f1-87cb-434c-b19c-95cd11f1a583)

Further data can be extracted for each page of text.   For now, we can build a graph using the data extracted in each printout block above.

The dollar amounts for each unique EAL code type are agregated below.  The columns are the total dollars, the average dollars, and the # of report sections contributing dollars. 

![image](https://github.com/kwd2/aurora1/assets/15908030/7cf715c9-0b82-4350-b0da-aee46b933a6b)

The FUND information can be added to the graph below.  Adding the highlighted line of code causes the second order graph to accumulate and printout as shown.

![image](https://github.com/kwd2/aurora1/assets/15908030/3e107f90-cd0d-4012-a808-4f681e0ec4e0)




