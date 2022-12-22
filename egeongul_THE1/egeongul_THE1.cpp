#include <iostream>
using namespace std;


void getInput(string exercise, double & mins, double & reps){
    
    cout << exercise << ": " ;
    cin >> mins >> reps;

}


void getInput2(string exercise, double & mins, double & reps, double & liftedWeight){
    
    cout << exercise << ": " ;
    cin >> mins >> reps >> liftedWeight;
}


bool inputCheck(double reps, double mass, double minute, double liftedWeight){
    if (mass < 30){
        cout << "Weight out of range!"<< endl;
        return false;
    }
    else if (reps < 0 || reps >50){
        cout << "Reps out of range!" << endl;
        return false;
    }
    else if (minute < 0 || minute >2000){
        cout << "Minute out of range!"<< endl;
        return false;
    }
    else if ( liftedWeight <=0 || liftedWeight >35 ){
        cout << "Lifted weight out of range!"<< endl;
        return false;
    }
    else {
        return true;
    }
}

double computeResults(double mass, double goal, double metLunge, double metPushUp, double metPullUp,  double metWeightLift, double lungesMin, double pushUpMin, double pullUpMin, double weightMin){
    
    double calorieLunge = lungesMin * (metLunge * 3.5 * mass) /200;
    double caloriePushUp = pushUpMin * (pushUpMin * 3.5 * mass) /200;
    double caloriePullUp = pullUpMin * (metPullUp * 3.5 * mass) /200;
    double calorieWeightLift = weightMin * (metWeightLift * 3.5 * mass) /200;
    return calorieLunge + caloriePullUp + caloriePushUp + calorieWeightLift ;
    
}


int main (){
    
    double lungesMin, lungesRep, pushUpMin, pushUpRep, pullUpMin, pullUpRep, mass, liftedWeight, weightMin, weightRep, goal, metLunge, metPushUp, metPullUp, metWeightLift  ;
    string name;
    cout << "Please enter your name: " ;
    cin >> name;
    cout << "Welcome " << name << ", please enter your weight(kg): ";
    cin >> mass;
    cout << name << ", please enter minutes and repetitions in a week for the activities below." << endl;

    getInput("Lunges", lungesMin, lungesRep);
    getInput("Push Ups", pushUpMin, pushUpRep);
    getInput("Pull Ups", pullUpMin, pullUpRep);
    cout << name <<", please enter minutes, repetitions and lifted weight in a week for the activities below."<< endl ;
    getInput2("Weight Lifting", weightMin, weightRep, liftedWeight);
    cout << name << ", please enter your weekly calorie burn goal: " ;
    cin >> goal ;
    if (inputCheck(lungesRep, mass, lungesMin, liftedWeight)){
        if (inputCheck(pushUpRep, mass, pushUpMin, liftedWeight)){
            if (inputCheck(pullUpRep, mass, pullUpMin, liftedWeight)){
                if (inputCheck(weightRep, mass, weightMin, liftedWeight)){

                    //     *************************
                            if (lungesRep < 15 ){
                                metLunge = 3;
                            }
                            else if (lungesRep <30){
                                metLunge = 6.5;
                            }
                            else {
                                metLunge = 10.5;
                            }
                    //      *************************
                            if (pushUpRep < 15 ){
                                metPushUp = 4;
                            }
                            else {
                                metPushUp = 7.5;
                            }
                    //      *************************
                            if (pullUpRep < 25 ){
                                metPullUp = 5;
                            }
                            else {
                                metPullUp = 9;
                            }
                    //      *************************
                            
                            if (liftedWeight < 5 && weightRep < 20){
                                metWeightLift = 3;
                            }
                            else if (liftedWeight < 5 && weightRep < 40){
                                metWeightLift = 5.5;
                            }
                            else if (liftedWeight < 5 && weightRep >= 40){
                                metWeightLift = 10;
                            }
                            else if (liftedWeight >= 5 && liftedWeight < 15 && weightRep < 20){
                                metWeightLift = 4;
                            }
                            else if (liftedWeight >= 5 && liftedWeight < 15 && weightRep < 40){
                                metWeightLift = 7.5;
                            }
                            else if (liftedWeight >= 5 && liftedWeight < 15 && weightRep >= 40){
                                metWeightLift = 12;
                            }
                            else if (liftedWeight > 15 && weightRep < 20){
                                metWeightLift = 5;
                            }
                            else if (liftedWeight > 15 && weightRep < 40){
                                metWeightLift = 9;
                            }
                            else {
                                metWeightLift = 13.5;
                            }
                    
                    
                    cout << "From lunges, you burned " <<  lungesMin * (metLunge * 3.5 * mass) /200 << " calories."<< endl;
                    cout << "From push ups, you burned " << pushUpMin * (metPushUp * 3.5 * mass) /200 << " calories." << endl;
                    cout << "From pull ups, you burned " << pullUpMin * (metPullUp * 3.5 * mass) /200 << " calories."<< endl;
                    cout << "From weight lifting, you burned " << weightMin * (metWeightLift * 3.5 * mass) /200 << " calories." << endl;
                    
                    double total = lungesMin * (metLunge * 3.5 * mass) /200 + pushUpMin * (metPushUp * 3.5 * mass) /200 + pullUpMin * (metPullUp * 3.5 * mass) /200 + weightMin * (metWeightLift * 3.5 * mass) /200 ;
                    
                    cout << "You burned " << total << " calories."<< endl;
                    cout << endl ;
                    
                    
                    
                    if (total > goal){
                        cout << "You have surpassed your goal! You can eat something worth " << total-goal <<" calories :)" << endl;
                    }
                    if ( total == goal){
                        cout << "Congratulations! You have reached your goal!"<< endl;
                    }
                    
                    if (total < goal){
                        cout << "You did not reach your goal by " << goal-total << " calories." << endl;
                        cout << "You need to do lunges " << (goal-total)/((metLunge * 3.5 * mass) /200) << " minutes more to reach your goal or," << endl;
                        cout << "You need to do push ups " << (goal-total) /  ((metPushUp * 3.5 * mass) /200) << " minutes more to reach your goal or," << endl;
                        cout << "You need to do pull ups " <<  (goal-total) /  ((metPullUp * 3.5 * mass) /200) << " minutes more to reach your goal or," << endl;
                        cout << "You need to do weight lifting " << (goal-total) / ((metWeightLift * 3.5 * mass) /200) << " minutes more to reach your goal." << endl;
                        
                    }
                }
            }
        }
    }
    
    
    
    return 0;
    
}
