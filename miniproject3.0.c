#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct customer customer;   // structure for customer details Array
 struct customer{
    long long int accNo,cardNo,phoneNo;
    int pin,balance;
};

typedef struct transaction transaction;   // structure for transactions SLL
 struct transaction{
    //char transId[15];
    long long int senderAcc,receiverAcc;
    int transAmount;
    transaction *link;
}*new,*head=NULL,*last=NULL,*temp;

void create(long long int inputAccNo,long long int receiverAccNo,int inputAmount)   // create functioin for transactions SLL
{   
    new= (transaction *)malloc(sizeof(transaction));
    new->link= NULL;
    //new->transId=printId;
    new->senderAcc=inputAccNo;
    new->receiverAcc=receiverAccNo;
    new->transAmount=inputAmount;
}

 // insert function for transactions occured
void insert(long long int inputAccNo,long long int receiverAccNo,int inputAmount) 
{
    create(inputAccNo,receiverAccNo,inputAmount);
    if(head==NULL)
    {
        head=new;
        last=new;
    }
    else
    {
        last->link=new;
        last=new;
    }
}

void display(long long int account)  // display function for printing transactions
{   
    int flag=0;
    if(head==NULL)
        printf("\nYour Account has no transaction records!!!\n");
    else{
        temp=head;
        printf("\nTransacions Occured : \n");
        while(temp!=NULL)
        {   
            if(temp->senderAcc==account || temp->receiverAcc==account)
            {
                printf("%lld %lld %d\n",temp->senderAcc,temp->receiverAcc,temp->transAmount);
                flag=1;
            }
            temp=temp->link;
        }
        if(flag==0)
                printf("\nYour account has no transaction records!!!\n");
    }
}

int pinChange(long long int inputCardNo);

void main()
{   
    customer c1[5];
    c1[0].accNo=99900009999;
    c1[0].cardNo=8888000044441111;
    c1[0].phoneNo=7782090024;
    c1[0].pin=9090;
    c1[0].balance=55000;

    c1[1].accNo=44449993333;
    c1[1].cardNo=1122334455667788;
    c1[1].phoneNo=9798979700;
    c1[1].pin=1200;
    c1[1].balance=14500;

    c1[2].accNo=55339000111;
    c1[2].cardNo=5555333311112222;
    c1[2].phoneNo=9845835633;
    c1[2].pin=7788;
    c1[2].balance=2300;

    c1[3].accNo=54547777390;
    c1[3].cardNo=9090888822114444;
    c1[3].phoneNo=9934460090;
    c1[3].pin=2001;
    c1[3].balance=455500;

    c1[4].accNo=33311119999;
    c1[4].cardNo=2222000055551111;
    c1[4].phoneNo=8860777711;
    c1[4].pin=1115;
    c1[4].balance=77000;
    
    int choice,ch,i,flag=0,flag2=0;
    int inputPin,newPin;
    int inputAmount,inputBalance;
    long long int inputCardNo,inputAccNo,receiverAccNo; 
    int withdrawAmount;
    
    printf("\t---------------------------------------------------------------------------------------------\n");
    printf("\n\t\t\t\t\tWelcome to B21 Digit34eal Atm\n");
    labelAuth: printf("\nEnter your Atm Card Number : ");
    scanf("%lld",&inputCardNo);
    printf("Enter your PIN : ");
    scanf("%d",&inputPin);
    flag=0;
    for(i=0;i<5;i++){
        if(inputCardNo==c1[i].cardNo && inputPin==c1[i].pin)
        {   
            flag=1;
            inputAccNo=c1[i].accNo;
            inputBalance=c1[i].balance;
        }
    }
    if(flag==0)
    {
        printf("\nInvalid credentials!\nPlease try again...\n\n");
        goto labelAuth;
    }
    else
    {
        labelChoice: printf("\n1. Withdraw\n");
        printf("2. Transfer Money\n");
        printf("3. PIN Change\n");
        printf("4. Mini Statement\n");
        printf("5. Balance Enquiry\n");
        printf("6. Back to Login Page\n");
        printf("7. Exit\n");
        printf("Enter your choice : ");
        scanf("%d",&choice);
        for(i=0;i<5;i++){
            if(inputCardNo==c1[i].cardNo && inputPin==c1[i].pin)
            {   
                flag=1;
                inputAccNo=c1[i].accNo;
                inputBalance=c1[i].balance;
            }
        }
        switch(choice)
        {
            case 1: labelWithdraw: printf("\nEnter amount to withdraw: ");
                    scanf("%d",&withdrawAmount);
                    if(withdrawAmount<=0)
                    {
                        printf("\nAmount must be greater than 0 \nTry Again!!!\n");
                        goto labelWithdraw;
                        
                    }
                        if(inputBalance<withdrawAmount)
                        {
                            printf("Insufficient balance!!!\n");
                            goto labelChoice;
                        }
                        else
                        {   
                            for(i=0;i<5;i++)
                            {
                                if(inputCardNo==c1[i].cardNo)
                                {   
                                    c1[i].balance-=withdrawAmount;
                                    printf("\nRs.%d has been withdrawal sucessfully...\n",withdrawAmount);
                                    printf("Remaining balance: %d\n",c1[i].balance);
                                    insert(inputAccNo,inputAccNo,withdrawAmount);
                                }
                            }
                        }
                    break;
            case 2: labelConfirmAcc: printf("\nEnter receiver's account number: ");
                    scanf("%lld",&receiverAccNo);
                    for(i=0;i<5;i++)
                    {   
                        if(receiverAccNo==c1[i].accNo)
                            flag2=1;
                    }
                    
                    if(flag2==1)
                    {
                        printf("\nDo you want to transfer money to Account number %lld\n",receiverAccNo);
                        printf("Enter 1 to transfer or 0 to re-enter account number: ");
                        scanf("%d",&ch);
                        if(ch!=1)
                            goto labelConfirmAcc;
                        printf("\nEnter amount to be transferred: ");
                        scanf("%d",&inputAmount);
                        if(inputAmount<=0)
                        {
                            printf("\nAmount must be greater than 0\nTransaction cancelled...\nTry Again!!!\n");
                            goto labelConfirmAcc;
                        }
                        if(inputBalance<inputAmount)
                        {
                            printf("Insufficient Balance...\n");
                            goto labelChoice;
                        }
                        else{
                            for(i=0;i<5;i++)
                            {
                                if(inputCardNo==c1[i].cardNo)
                                {
                                    c1[i].balance-=inputAmount;
                                    printf("Your Account's remaining balance : %d\n",c1[i].balance);
                                }
                            }
                            for(i=0;i<5;i++)
                            {
                                if(receiverAccNo==c1[i].accNo)
                                {
                                    c1[i].balance+=inputAmount;
                                    //printf("Receiver balance = %d\n",c1[i].balance);
                                    printf("Rs.%d has been transferred sucessfully to Account number %lld\n",inputAmount,receiverAccNo);
                                }
                            }
                        }
                        insert(inputAccNo,receiverAccNo,inputAmount);
                    }
                    else
                    {
                        printf("This Account do not exits...\nTry Again!");
                        goto labelConfirmAcc;
                    }
                    break;
            case 3: newPin=pinChange(inputCardNo);
                    if(newPin<0)
                    {
                        printf("\nInvalid input\nPin must be positive\n");
                        break;
                    }
                    for(i=0;i<5;i++)
                    {
                        if(inputCardNo==c1[i].cardNo)
                        {   
                            printf("\nPIN changed sucessfully...\n");
                            printf("Previous Pin is %d\n",c1[i].pin);
                            c1[i].pin=newPin;
                            printf("New PIN : %d\n",c1[i].pin);
                        }
                    }
                    break;
            case 4: display(inputAccNo);
                    break;
            case 5: for(i=0;i<5;i++)
                    {
                        if(inputCardNo==c1[i].cardNo)
                            printf("\nYour Account balance is Rs.%d\n",c1[i].balance);
                    }
                    break;
            case 6: goto labelAuth;        
            case 7: exit(0);
                    break;
            default: printf("\nInvalid choice...\nPlease enter a valid choice between 1 to 6\n");
        }
        goto labelChoice;
    }
}

int pinChange(long long int inputCardNo)
{   int newPin,confirmPin,changedPin;
    labelPinChange: printf("\nEnter New PIN (4-digit only): ");
    scanf("%d",&newPin);
    printf("Confirm New PIN : ");
    scanf("%d",&confirmPin);
    if(newPin==confirmPin)
        changedPin=newPin;
    else
    {   
        printf("\nPin did not match...\nTry Again!\n");
        goto labelPinChange;
    }
    return changedPin;
}