/*




*/

#include <apc.h>


dig *eval_sum(dig **No1, dig **No2, char operator) {
    dig *Result = NULL;
    dig *ptr1 = *No1, *ptr2 = *No2, *ptr = NULL;
    int carry_flag = 0, result, idx = 0;
    dl_print_list(ptr1);

    dl_print_list(ptr2);

    while (ptr1->nextD != NULL) {
        if (operator == '-') {
            ptr1->cur = ~(ptr1->cur) + 1;
    //        printf("%d",ptr1->cur);
        }
        ptr1 = ptr1->nextD;
    }

    if (operator == '-') {
        ptr1->cur = ~(ptr1->cur) + 1;
    }

    if (ptr2 == *No2 && ptr2->cur < 0) {
        ptr2->cur = ptr2->cur * -1;
    }

    while (ptr2->nextD != NULL) {
        ptr2 = ptr2->nextD;
    }

    if (operator == '+' || operator == '-') {
        while (ptr1 != NULL || ptr2 != NULL) {
            if (ptr1 != NULL && ptr2 != NULL) {
                if (operator == '-' && ptr2 != *No2 && ptr2->cur < (ptr1->cur * -1)) {
                    ptr = ptr2;
      //              printf("fjhjfh");
                    while (ptr->prevD->cur == 0 && ptr != NULL) {
                        ptr = ptr->prevD;
        //                printf("djhdhj");
                        if (ptr == *No2) {
                            break;
                        }
                    }
                    if (ptr != NULL) {
                        if (ptr != *No2)
                            ptr = ptr->prevD;
                        ptr->cur = ptr->cur - 1;
                        dl_print_list(ptr);
                        ptr = ptr->nextD;
                        while (ptr != ptr2) {
                            ptr->cur = ptr->cur + 10000 - 1;
                            ptr = ptr->nextD;
                        }
                        ptr->cur = ptr->cur + 10000;
                    }
                }
                dl_print_list(*No2);
                result = ptr1->cur + ptr2->cur + carry_flag;
               // printf("%d",result);
            } else if (ptr1 == NULL && ptr2 != NULL) {
                result = ptr2->cur + carry_flag;
            } else if (ptr2 == NULL && ptr1 != NULL)
                result = ptr1->cur + carry_flag;

            carry_flag = 0;
            if (result > 99999999) {
                carry_flag = 1;
                result = result - 100000000;
            }

            dl_insert_first(&Result, result);
            dl_print_list(Result);

            if (ptr1 != NULL)
                ptr1 = ptr1->prevD;

            if (ptr2 != NULL)
                ptr2 = ptr2->prevD;
        }
    }

    if (carry_flag == 1 && operator == '+') {
        dl_insert_first(&Result, 1);
    }

    if (operator == '-') {
        ptr = Result->nextD;
        while (ptr != NULL) {
            if (ptr->cur < 0)
                ptr->cur = ptr->cur * -1;
            ptr = ptr->nextD;
        }
        ptr1 = *No1;
        while (ptr1 != NULL) {
            if (operator == '-') {
                ptr1->cur = ~(ptr1->cur) + 1;
            }
            ptr1 = ptr1->nextD;
        }
    }
    dl_print_list(Result);
    return Result;
}
