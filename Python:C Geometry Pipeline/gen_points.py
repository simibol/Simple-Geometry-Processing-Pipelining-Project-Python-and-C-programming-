import math
import random
import sys
import argparse

def point_generation(mindist, N, rseed = None): #rseed is defaulted to none as it is an optional parameter

    if rseed != None:       #sets a seed for the random number generator if rseed is provided
        random.seed(rseed) 
    
    points_array = []  #initialises an array for the points to be appended to

    def point_distance(point_1, point_2): # finding distance between the 2 points (for mindist calculations)

        return math.sqrt((point_1[0] - point_2[0])**2 + (point_1[1] - point_2[1]) **2)

    def min_distance(point, other_point): #checks minimum distance between the 2 points is valid

        for other_points in other_point:
            if point_distance(point, other_points) < mindist:
                return False
        return True

    for i in range(N):

        while True: # creates the x and y coordinates of the new_point, in the range, rounded to 2 decimal places
            x_coord = round(random.uniform(-50, 50), 2)
            y_coord = round(random.uniform(-50, 50), 2)
            
            

            new_point = (x_coord, y_coord)

            if min_distance(new_point, points_array): # appends point to array if it passes the above conditions
                points_array.append(new_point)
                break
    

    return points_array

def main():



    try:

        process_equal_args = []      #to process the equals sign to allow for the correct formatting with the A1 guidelines
        for arg in sys.argv[1:]:
            if "=" in arg:
                process_equal_args.extend(arg.split('='))
            else:
                process_equal_args.append(arg)

        #to parse in the argument, allowing for them to be presented in any order
        
        parser = argparse.ArgumentParser(description = "Generation of random 2D points with a minimum distance between")
        parser.add_argument("-mindist", type=int, required= True, help= "The minimum distance between points")
        parser.add_argument("-N", type=int, required= True, help= "The amount of points to generate")
        parser.add_argument("-rseed", type=int, nargs="?", default= None, help= "optional random seed")

        args = parser.parse_args(process_equal_args)

        

        try:
            args = parser.parse_args() #checking if the right arguments are processed
        except argparse.ArgumentError:
            sys.stderr.write("invalid arguments")
            sys.exit(-4)

        if args.N < 0:              #N cannot be less than zero
            sys.stderr.write("N less than zero\n")
            sys.exit(-1)
        
        if args.mindist < 0 or args.mindist > 10:    #mindist has to be in the range 0-10
            sys.stderr.write("mindist outside range\n")
            sys.exit(-2)
        
        if args.N > (10000/(math.pi * (args.mindist)**2)):
            sys.stderr.write("point saturation")
            sys.exit(-3)
        
        #making sure the arguments are in the command

        if not (isinstance(args.mindist, int) and isinstance(args.N, int) and (args.rseed is None or isinstance(args.rseed, int))): 
            sys.stderr.write("invalid arguments")
            sys.exit(-4)

        resultant_points = point_generation(args.mindist, args.N, args.rseed) #get the points from the command line

        for point in resultant_points: #printing the points
            print(f"{point[0]:.2f}, {point[1]:.2f}", file=sys.stdout)

    except BrokenPipeError:
        sys.stderr.close()


if __name__ == "__main__":
    main()

    