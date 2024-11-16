int flag=0;
do
{
    system("clear");




    printf("\n1. Run again\n");
    printf("0. Exit\n");
    int choice=0;
    printf("Enter your choice : ");
    scanf("%d",&choice);
    
    switch (choice)
    {
    case 1:
        flag=1;
        break;
    case 0:
        flag=0;
        break;
    
    }
} while (flag==1);
