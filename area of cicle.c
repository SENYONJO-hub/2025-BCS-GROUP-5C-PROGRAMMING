/*This program prompt the user to input radius in order to clculate the area of a Circle*/
#include <stdio.h>
int main(){
    int radius; 
    float  area;
    printf("Enter the radius of the circle: ");
    scanf("%d", &radius);
    area = 3.14159 * radius * radius; // Area = πr²
    printf("The area of the circle with radius %d is %.4f\n", radius, area);
    return 0;
}