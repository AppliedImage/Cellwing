//AngleGoer
  //This code has the servo motor go to the correct angle.
//Variables:
//  int: Latitude;
//  int: Longitude;
//  time: time;
//  int: altitude;
//  int: 
//Function: SunPositionFinder   
  // This function will take as input the tim, lat, and lon, and overcast
  // and will output the correct angle for the motor to point at the sun.
//Function: CloudCoverOptimizer 
  // this function calls sun position finder, takes in info from the weather api, 
  // and then responds with a boolean for overcast.
//Function: SafePositionCalculator 
  // This function is called by AngleGoer, calls CloudCoverOptimizer, and takes 
  // input from the weather api of current wind speed and direction, and returns the most optimum safe location for blades. 
//Function: ServoMover
  // This function is called by AngleGoer, and takes the most optimum safe location for the blades and travels to it.

void setup(){
  Serial.begin(115600);
  int: timH;
  int: timM;
  int: lat;
  int: lon;
  int: alt;  // Will use this in future iterations
  int: overcast;
  int: windSpeed;
  int: windDirection;
  int: thetaBase; // this is the direction of the 360 degrees rotation of the base motor wrt the cardinal directions- east equals 0
  int: thetaFoil; // this is the angle of the foils spread outward
  int: phiPanel; // this is the direction of the 90 degrees of the angle of the panel
  int: safeBase; // this is the safe direction of the base wrt wind direction
  int: safeFoil; // safe angle of foil wrt wind speed and direction
  int: safePanel; // safe angle of panels wrt gustrisk
  int: gustRisk; // risk of wind being a gust above a safe level.
  int: gustDirection; //direction from potentialgust
  Servo Base;
  Servo Foil;
  Servo Panel;
  base.attach(9)
  foil.attach(10)
  Panel.attach(11)

}

void loop() {


thetaBase, thetaFoil, phiPanel = sunPositionFinder(timH, timM, lat, lon, alt);
safeBase, safeFoil, safePanel = safePositionCalculator(thetaBase, thetaFoil, phiPanel, windSpeed, windDirection);
servoMover(base, safeBase);
servoMover(foil, safeFoil);
servoMover(panel, safePanel);


}








int SunPositionFinder(timH, timM, lat, lon, alt){
 //edit equation for raw time inputs
 theta = asin((cos(L)*cos(phi)*cos(H))+(sin(L)*sin(theta)))
 phi = asin((cos(theta)*sin(H))/cos(beta));
 
 thetaBase, thetaFoil, phiPanel = cloudCoverOptimizer(theta, phi, overcast);
 return thetaBase, thetaFoil, phiPanel;
 
}





int CloudCoverOptimizer(phi, overcast){

//In overcast days, majority of light striking panel is diffuse. When panel angle is 90 deg it sees half of sky
//when panel angle is horizontal it sees whole sky. 
// Controlling eqn is Idh = (0.095 + 0.04*sin((360/365)*(n-100)))*Ib
//where Ib is flux entering earth's surface

//What level of gains can be had from overcast day optimization? For low overcast areas, <<, but for high, >>.
//How does this intereact with gust likelihood and weather conditions? 

// likelu enable function in regions that have high overcast/low gust. Low overcast/high gust should focus on gust mitigation.

//For now: 

if(overcast>128){
  phiPanel = (phiPanel + 10);
}
  return phiPanel;
}


int GustRiskCalculator(windSpeed, windDirection){
  // Get numbers from Makalya M on how to calculate gust risk- if no response by 11/3, reach out to Randy H.
  return gustRisk, gustDirection;
}


int SafePositionCalculator(thetaBase, thetaFoil, phiPanel, windSpeed, windDirection){
  //this code is placeholder code- research needs to be done on best positions for a given gust risk.
  
  gustRisk, gustDirection = gustRiskCalculator(windSpeed, windDirection);
  if (gustRisk >128){
    thetaBase = (thetaBase + gustDirection)/2;
    thetaFoil = (thetaFoil - 10);
    phiPanel = (phiPanel-10);
  }
  return thetaBase, thetaFoil, phiPanel;
}




int ServoMover(ServoSelected, angleTarget){
  
// move from 0 to 180 degrees with a positive angle of 1
  for(angle = 0; angle < 180; angle += 1) { ServoSelected.write(angle); delay(15); } delay(1000); // move from 180 to 0 degrees with a negative angle of 5 for(angle = 180; angle>=1; angle-=5)
  {                                
    ServoSelected.write(angle);
    delay(5);                       
  } 

    delay(1000);

}
