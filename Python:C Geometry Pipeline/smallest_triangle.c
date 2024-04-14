#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POINTS 1000
#define BUFFER_SIZE 100


typedef struct { // to represent a 2D point
    double x_coord;
    double y_coord;
} Point;

double distance(Point point_1, Point point_2){ //using the Euclidean Distance Metric between 2 points
    
    return sqrt(pow(point_1.x_coord - point_2.x_coord, 2) + pow(point_1.y_coord - point_2.y_coord, 2));
}

double area_of_triangle(Point point_1, Point point_2, Point point_3){

    double side_a = distance(point_1, point_2); // finding the side lengths of the sides between the 3 points
    double side_b = distance(point_2, point_3);
    double side_c = distance(point_1, point_3);
    double semi_perimeter = (side_a + side_b + side_c) / 2;
    // below is Heron's formula to find the area using the 3 side lengths and semi-perimeter:
    double area = sqrt(semi_perimeter * (semi_perimeter-side_a) * (semi_perimeter-side_b) * (semi_perimeter-side_c));
    return area;
}

int main(){

    Point points[MAX_POINTS]; //maximum number of points that the program can intake is 1000, stored in the array.
    char buffer[BUFFER_SIZE]; //storing each input line
    int count = 0; // counting the number of points its intaking
    double x_coord;
    double y_coord; //storing coordinates temporarily

    //looping through all the points
    while (count < (MAX_POINTS) && fgets(buffer, sizeof(buffer), stdin) != NULL){
        if(sscanf(buffer, "%lf, %lf", &x_coord, &y_coord) == 2){ //returning number of successful points
            if(x_coord >= -50 && x_coord <= 50 && y_coord >= -50 && y_coord <= 50){
                points[count].x_coord = x_coord;
                points[count].y_coord = y_coord;
                count++;
            }
        }           //above is scanning through all the point inputs, making sure there's less than 1000 points, and that all the points
                    //are within the range of (-50,50) and storing them in the array "Point"
        
    }
    

    printf("read %d points\n", count); //printing the desired output with how many points are found

    if(count < 3){  // Checking the triangle separately if their is less than 3 points
        for (int i = 0; i < count; i++){ 
            printf("%.2f, %.2f\n", points[i].x_coord, points[i].y_coord);
        }
        printf("This is not a triangle\n");
        return 0;
    }
    



    double minimum_three_sides_sum = INFINITY; 

    Point closest_points[3]; //traversing through the combinations of 3 points from the input to find the ones that are the closest

    for (int i = 0; i < count - 2; i++){
        for (int j = i+1; j < count - 1; j++){
            for (int k = j+1; k < count; k++){
                
                double a_side = distance(points[i], points[j]); //uses the "distance" function created above to measure each distance in the traversal
                double b_side = distance(points[j], points[k]);
                double c_side = distance(points[i], points[k]);

                double side_sum = a_side + b_side + c_side;

                if(side_sum < minimum_three_sides_sum){

                    minimum_three_sides_sum = side_sum; //checks to see if the current side sum in the traversal is found
                                                            //and resets the minimum 3 sides sum to it

                    closest_points[0] = points[i]; // sets the closest points to those ones found to be the minimum
                    closest_points[1] = points[j];
                    closest_points[2] = points[k];
                }
            }
        }
    }
    //below uses the closest points and the function created ("area_of_triangle") to find the area of the triangle with those points:
    double new_triangle_area = area_of_triangle(closest_points[0], closest_points[1], closest_points[2]);
    
    
    for(int i = 0; i<3; i++){
        printf("%.2f, %.2f\n", closest_points[i].x_coord, closest_points[i].y_coord);
    }
    if(new_triangle_area > 0.001){ //making sure it is a triangle
        printf("This is a triangle\n");

    } else {
        printf("This is not a triangle\n");
    }


    return 0;
}