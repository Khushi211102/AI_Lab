% Facts about car types and their categories
car_type(sedan, luxury).
car_type(suv, utility).
car_type(coupe, sporty).
car_type(hatchback, economy).

% Facts about user preferences
user_likes(john, luxury).
user_likes(mary, sporty).
user_likes(peter, utility).

% Facts about car ownership (replace with actual data)
owns(john, suv).  % John already owns a sedan

% Recommend car based on user and category (helper predicate)
recommend_car_by_category(User, Category, Car) :-
  car_type(Car, Category),
  \+ owns(User, Car).  % User doesn't already own the car

% Recommend car based on user preferences
recommend_car(User, RecommendedCar) :-
  user_likes(User, Category),
  recommend_car_by_category(User, Category, RecommendedCar).

% Example usage
% recommend_car(john, RecommendedCar) will output the recommended car for John
