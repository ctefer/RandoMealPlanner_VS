# RandoMealPlanner_VS
The RandoMealPlanner is designed to generate meals and a grocery list based on meals established in the entrees.csv file. Sides and Starches may be added
to each meal in sides.csv and starches.csv. Regular grocery items may be added to the grocery list in regulars.csv. Entree items contain a list of all
grocery items needed for the item. These items must be present in the grocery list to be added. The grocery list breaks down the items into categories
so that when you go to get the items you can find them in the appropriate aisle. 

The grocery aisle function is a future idea for addition to OurGroceries shopping list app.


Build using GCC version 3.16
_$ mkdir build
_$ cmake ..
_$ make

_$ ./RandoMealPlanner [FOLDER:{CSV_FOLDER}] [DAYS:{INT}]
