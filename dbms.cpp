
//write a program to find the closure of the attribute , candidate key , equivalence of the two functional dependencies and noraml form.

/*Schema : EMP(eid,ename,dept,age,salary,experience) //where EMP is the relation

Let the functional dependencies be as follows:

eid->ename
{age,experience}->salary
eid->{age,dept}
dept->experience

In above example, let us find the closure of the attribute eid, i.e, closure of {eid}

Since we are finding closure of eid. eid is an element of the closure set C+. Now we go step by step.



Step 1: Select each functional dependency and check whether the left side of functional dependency is a subset of closure. If yes, add the right side of that functional dependency to closure set. if not, check the next functional dependency

Step 2: Keep on checking the functional dependencies until there is no more functional dependencies with its left side as a subset of closure set C+.

What is a subset? 
A set M is said to be a subset of another set N only if all elements of set M is present in set N.
Set N can have more elements than M.


So, in our example, eid is an element of the closure set C+. So, initially, C+={eid}.
First functional dependency says eid functionally determines ename.
Its left side ( {eid}) is subset of C+. 
Therefore, its right side is added to C+. Now C+={eid,ename}. 
Second fd (functional dependency) says {age,experience}->salary.
Here left side ( {age,experience} ) is not a subset of C+. So we check the next fd.
Third fd says, eid->{age,dept}.
Here left side ( {eid} ) is subset of C+.
Therefore, its right side is added to C+.
Now, C becomes, C+={eid,ename,age,dept}.
Fourth fd says, dept->experience. 
Here left side ( {dept} ) is a subset of C+.
So we are adding its right side ( {experience} ) to Closure set. 
Now, C+={eid,ename,age,dept,experience}.
We are looking again for a functional dependency with its left side as a subset of closure set. 
Since the closure set C+ is getting changed in some steps, there is more possibility to find another functional dependency with it s left side as a subset of C+. 
Again we go through every functional dependency. 
Since sets do not allow duplication, we should do nothing if the right side of the a functional dependency whose left side is subset of C+, is already present in closure set C+.
Second fd has a left side that is subset of C+. {age,experience}->salary. Therefore salary is added to C+. 
Now, C+={eid,ename,age,dept,experience,salary}.
There isn't any more functional dependency whose left side is subset of C+ and give at least one new attribute to closure set. Therefore we stop now.
Now closure of set C is C+={eid,ename,age,dept,experience,salary}.*/

/*Algorithm to Find Candidate Key from Functional Dependencies
First of all, we will see the algorithm to find candidate keys from functional dependencies. The input is functional dependencies.

Algorithm:

1. Find the attributes that are neither on the left and right side

2. Find attributes that are only on the right side

3. Find attributes that are only on the left side

4. Combine the attributes on step 1 and 3

5. Test if the closures of attributes on step 4 constitutes all the attributes. If yes it is a candidate key.

6. If not, find the relation exteriors, that is the attributes not included in step 4 and step 2.

7. Now test the closures of attributes on step 4 + one attribute in step 6 one at a time. 
All those combinations are candidate keys if their closures constitute all the attributes. */

#include<iostream> 
#include<stdio.h>
#include<string.h>
#include<conio.h>
using namespace std;
struct fd //functional dependency representation
   {
   int left[8];  //for left side of fd
   int right[8];  //for right side of fd
   int lcount,rcount;
   }f[10];


int attrcount,closcount=0,fdcount;
int closure[10];
char attr[10][25];
int nolnor[8],ronly[8],lonly[8],merg1n3[8],exteriors[8];

void getclosure();
void get_nolnor();
void get_ronly();
void get_lonly();
void get_merg1n3();
int iscomplete();

void getclosure()  //to find the closure of the attribute
 {
int i,j,k,l=0,issubset,found;
do
    {
    for(i=0;i<=fdcount;i++)//Checking each functional dependancy
      {
      issubset=1;
      for(j=0;j<f[i].lcount;j++)//select each attribute in leftside
         {
         found=0;
         for(k=0;k<closcount;k++) //checking with each element of closure
            {
            if(closure[k]==f[i].left[j])  //if the closure of the attribute is same as
                                          //the left side of the fd then we have to take 
                                          //this attribute in the closure of the resp. attribute. 
               {
               found=1;//true then break
               break;
               }
            }
         if(found==0) //if not found then also break and search the other fd 
            {
            issubset=0;
            break;
            }
         }
      if(issubset==1)
         {
         for(k=0;k<f[i].rcount;k++)
            {
            found=0;
            for(j=0;j<closcount;j++)
               {
               if(closure[j]==f[i].right[k])
                  found=1;
               }
            if(found==0)
               {
               closure[closcount]=f[i].right[k];
               closcount++;
               }
            }
         }
      }
    l++;
    }while(l<attrcount);
}

void get_nolnor()  //find the attributes that are neither on the left and right side.
{                   //this is step 1 for finding candidate key
   int i,found,j,k,l=0;
   for(i=0;i<attrcount;i++)//take an attribute
    {
      found=0;
      for(j=0;j<=fdcount;j++) //take an fd
          {
          for(k=0;k<f[j].lcount;k++) //check in left
           

{
            if(i==f[j].left[k])
               {
             

found=1;
               break;
               }
            }
          if(found==1) //stop if found.
           

break;
          for(k=0;k<f[j].rcount;k++) //check in right
           

{
            if(i==f[j].right[k])
               {
             

found=1;
               break;
               }
            }
          if(found==1) //stop if found.
           

break;
          }
      if(found==0)
       {
         nolnor[l]=i;
         l++;
         }
      }
 nolnor[l]=222;
 }


void get_ronly()  //find the attributes that are only on the right side
 {                 //this is step 2 for finding candidate key
   int rpresent,lpresent,i,j,k,l=0;
   for(i=0;i<attrcount;i++)//take an atrribute
    {
      rpresent=0;
      for(j=0;j<=fdcount;j++)//take an fd
       {
         for(k=0;k<f[j].rcount;k++)
          

{
            if(i==f[j].right[k])
             

{
               rpresent=1;
               break;
               }
            }
         if(rpresent==1)
          

break;
         }
      lpresent=0;
      if(rpresent==1)
       {
         for(j=0;j<=fdcount;j++)//take an fd
        {
          

for(k=0;k<f[j].lcount;k++)
           

{
             

if(i==f[j].left[k])
             

 {
                lpresent=1;
                break;
                }
             

}
          

if(lpresent==1)
             

break;
          

}
         }
      if(lpresent==0&&rpresent==1)
       ronly[l++]=i;
  }
   ronly[l]=222;
   }

void get_lonly()  //find the attributes that are only on the left side
 {                 //this is step3 for finding candidate key
   int rpresent,lpresent,i,j,k,l=0;
   for(i=0;i<attrcount;i++)//take an atrribute
    {
      lpresent=0;
      for(j=0;j<=fdcount;j++)//take an fd
       {
         for(k=0;k<f[j].lcount;k++) //looking in leftside
          

{
            if(i==f[j].left[k])
             

{
               lpresent=1;
               break;
               }
            }
         if(lpresent==1)
          

break;
         }
      rpresent=0;
      if(lpresent==1)
       {
         for(j=0;j<=fdcount;j++)//take an fd
        {
          

for(k=0;k<f[j].rcount;k++)//checking in right side
           

{
            

  if(i==f[j].right[k])
      {
                rpresent=1;
                break;
                }
             

}
          if(rpresent==1)
             

break;
          

}
         }
      if(lpresent==1&&rpresent==0)
         lonly[l++]=i;
      }
   lonly[l]=222;
 }


void get_merg1n3() //combine the attributes of nolnor() and lonly()
 {                 //this is step4 i.e. combine step1 and step3
   /* combine lonly and nolnor */
   int i,j;
   for(i=0,j=0;lonly[j]!=222;i++,j++)
    merg1n3[i]=lonly[j];
   for(j=0;nolnor[j]!=222;i++,j++)
    merg1n3[i]=nolnor[j];

   merg1n3[i]=222;
   }


int compare(char temp[25])
  {
   int i;
   for(i=0;i<attrcount;i++)
      {
      if(strcmp(temp,attr[i])==0)
      return i;
      }
  return 0;                                      
  }

int iscomplete()
 {
   if(closcount!=attrcount)
    return 0;
   else
    return 1;
   }


int main()
 {
   int i,j,k,attcode,found;
   char schema[100],temp[45],temp1[50];
   for(i=0;i<10;i++)
      {
      f[i].lcount=0;
      f[i].rcount=0;
      }
   //    printf("\nEnter the schema\n");   // enter the relation with the attributes
     //  scanf("%s",schema);

   cout<<"\nEnter the schema\n";   
   gets(schema);
   attrcount=0;
   for(i=0;schema[i]!='(';i++);

   do
      {
      j=0;
      i++;
      while(schema[i]!=','&&schema[i]!=')')
         {
         temp[j]=schema[i];
         j++;
         i++;
         }
      temp[j]='\0';
      strcpy(attr[attrcount],temp);
      attrcount++;
      }while(schema[i]==',');

   fdcount=-1;
   //printf("\nEnter the functional dependancies\nEnter 0 to stop\n");
   cout<<"\nEnter the functional dependancies\nEnter 0 to stop\n";
   for(i=0;i<10;i++)
      {
     //scanf("%s",temp1);
	  gets(temp1);
      if(strcmp(temp1,"0")==0)
         break;
      fdcount++;
      j=0;
      if(temp1[0]=='{'||temp1[0]=='(')
         j++;
      do
         {
         if(temp1[j]==',')
             j++;
         k=0;
         while(temp1[j]!=','&&temp1[j]!=')'&&temp1[j]!='}'&&temp1[j]!='-')
            {
            temp[k]=temp1[j];
            k++;
            j++;
            }
         temp[k]='\0';
         attcode=compare(temp);
         f[fdcount].left[f[fdcount].lcount]=attcode;
         f[fdcount].lcount++;
         }while(temp1[j]==',');
      if(temp1[j]==')'||temp1[j]=='}')
          j+=3;
      else if(temp1[j]=='-')
          j+=2;
      if(temp1[j]=='{'||temp1[j]=='(')
          j++;
      do
         {
         if(temp1[j]==',')
             j++;
         k=0;
         while(temp1[j]!=','&&temp1[j]!=')'&&temp1[j]!='}'&&temp1[j]!='\0')
            {
            temp[k]=temp1[j];
            k++;
            j++;
            }
         temp[k]='\0';
         attcode=compare(temp);
         f[fdcount].right[f[fdcount].rcount]=attcode;
         f[fdcount].rcount++;
         }while(temp1[j]==',');

      }
 cout<<"\nEnter an attribute whose closure is to be found\n";
 gets(temp);
 attcode=compare(temp);
 closcount=1;
 closure[0]=attcode;
 getclosure();
 cout<<"Closure of ";
 puts(temp);
 cout<<"\n";
 for(i=0;i<closcount;i++)
    {
    puts(attr[closure[i]]);
    }
    
    /*this is step 5 for finding candidate key
Test if the closures of attributes on step 4 are all the attributes*/
   closcount=0;
   for(i=0;merg1n3[i]!=222;i++)
    {
      closure[closcount++]=merg1n3[i];
      }
   getclosure();
 i=iscomplete();//check whether closure of merg1n3 is complete
   if(i==1)
    {
      cout<<"\nThe candidate key is:\n{";
      for(i=0;merg1n3[i]!=222;i++)
       {
         cout<< attr[merg1n3[i]];
         }
      //cout<<\b ;
      cout<<"}";
      }
   else
    {
/************** Step 6 **************
Find the relation exteriors, that is the attrbutes included not in 4 and not in 2
     included not in (ronly & merg1n3)
     */
      k=0;
      for(i=0;i<attrcount;i++)
       {
         found=0;
         for(j=0;ronly[j]!=222;j++)
          

{
            if(i==ronly[j])
             

{
               found=1;
               break;
               }
            }
         if(found==0)
          

{
            for(j=0;merg1n3[j]!=222;j++)
               {
             

if(i==merg1n3[j])
             

 {
                found=1;
                break;
                }
               }
            }
         if(found==0)
          

{
            exteriors[k++]=i;
            }
         }

      exteriors[k]=222;
      cout<<"Candidate Keys:";
/************** Step 7 **************
7. Now test the closures of attributes on step 4 + one attribute in step 6 one at a time.
*/
    for(k=0;exteriors[k]!=222;k++)
     {
       closcount=0;
       for(i=0;merg1n3[i]!=222;i++)
        {
        closure[closcount++]=merg1n3[i];
          

        }
       closure[closcount++]=exteriors[k];
       getclosure();
   i=iscomplete();//check whether closure of this instance of this step is complete
     if(i==1)
      {
          

      cout<<"{";
          

for(i=0;merg1n3[i]!=222;i++)
         {
           

cout<<attr[merg1n3[i]];
           

         }        
          

cout<<attr[exteriors[k]]<<endl;
          

}
       }
      }
 return 0;
}
