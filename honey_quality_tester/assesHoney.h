/*
   According to this youtube Video https://www.youtube.com/watch?v=Uf2g3FFGEd8&t=221s
   He stated that Pure Honey is between the pH of 3.4 to 6.1
   
   For Electric Conductivity
   He stated that Pure Honey's EC is depending on variant and which country, but mostly the value must be greater than 800 us/cm. 
*/
#define PH_MIN 3.2f    //change this value if need, just retain the "f" since it is a float
#define PH_MAX 6.1f    //change this value if need, just retain the "f" since it is a float
#define EC_MIN 800    // in uS/cm
#define MOISTURE_MAX 20

/*
   This value of absorbance is only base on the 2 samples of Honey given, 1 bottle of Pure and 1 bottle of Adulterated

   In my observation
   Pure has lower absorbance Value since it is clearer compare to Adulterated Honey. 

   This is not so accurate, It need more sample data to have more accurate reading
*/

#define VIOLET_CH1_THRESHOLD 0.3785f
#define VIOLET_CH2_THRESHOLD 0.4465f
#define BLUE_THRESHOLD 0.255f
#define GREEN_CH4_THRESHOLD 0.0615f
#define GREEN_CH5_THRESHOLD 0.192f
#define ORANGE_THRESHOLD 0.1235f
//#define RED_CH7_THRESHOLD 0.10f
//#define RED_CH8_THRESHOLD 0.05f
//#define CLEAR_THRESHOLD 0.10f
#define NIR_THRESHOLD 0.1968f
//bool isReal = true;

bool assessHoneyQuality(float pH, float EC, float moisture,float violetCh1, float violetCh2, float blue, 
                        float greenCh4, float greenCh5, float orange, float redCh7, 
                        float redCh8, float clear, float nir) {
    bool isPure = true;

    // Check pH
    if (pH < PH_MIN || pH > PH_MAX) { //less than 3.2 and more than 6.1 
        isPure = false;
        Serial.println("Adulterated: pH out of range.");
    }

    // Check electrical conductivity
    if (EC < EC_MIN) {   //less than 800 is adulterated
        isPure = false;
        Serial.println("Adulterated: Electrical conductivity too low.");
    }

    if (moisture > MOISTURE_MAX) { //  more than 20 is Adulterated
        isPure = false;
        Serial.println("Adulterated: Moisture too high.");
    }

    // Check spectral absorbance thresholds
    // if (violetCh1 < VIOLET_CH1_THRESHOLD) { //  less than 0.3785 is Adulterated
    //     isPure = false;
    //     Serial.println("Adultera   ted: Violet channel 1 absorbance too low.");
    // }

    // if (violetCh2 > VIOLET_CH2_THRESHOLD) { //  more than 0.4465 is Adulterated
    //     isPure = false;
    //     Serial.println("Adulterated: Violet channel 2 absorbance too high.");
    // }

    // if (blue > BLUE_THRESHOLD) {  //more than 0.255 is Adulterated
    //     isPure = false;
    //     Serial.println("Adulterated: Blue absorbance too high.");
    // }

    if (greenCh4 < GREEN_CH4_THRESHOLD) {     //less than 0.0615 is Adulterated
        isPure = false;
        Serial.println("Adulterated: Green channel 4 absorbance too high.");
    }

    // if (greenCh5 < GREEN_CH5_THRESHOLD) {     //less than 0.192 is Adulterated 
    //     isPure = false;
    //     Serial.println("Adulterated: Green channel 5 absorbance too high.");
    // }

    if (orange < ORANGE_THRESHOLD) {     //less than 0.1235 is Adulterated
        isPure = false;
        Serial.println("Adulterated: Orange absorbance too high.");
    }

    // if (redCh7 > RED_CH7_THRESHOLD) {
    //     isPure = false;
    //     Serial.println("Adulterated: Red channel 7 absorbance too high.");
    // }

    // if (redCh8 > RED_CH8_THRESHOLD) {
    //     isPure = false;
    //     Serial.println("Adulterated: Red channel 8 absorbance too high.");
    // }

    // if (clear > CLEAR_THRESHOLD) {
    //     isPure = false;
    //     Serial.println("Adulterated: Clear absorbance too high.");
    // }

    if (nir < NIR_THRESHOLD) {   //less than 0.1968 is Adulterated
        isPure = false;
        Serial.println("Adulterated: Near-IR absorbance too high.");
    }

    return isPure;
}