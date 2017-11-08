/* UNIVERSIDADE FEDERAL DE UBERLANDIA
   Biomedical Engineering
   Autors: Ítalo G S Fernandes
           Paulo Camargos Silva
           Nathalia Rodrigues
   contact: italogsfernandes@gmail.com
   URLs: https://github.com/italogfernandes/SEB
  Este codigo faz parte da disciplina de sinais e sistemas
  para engenhara biomedica e visa emular um gerador de sinais
  utilizando as portas DAC do Arduino Due
  Tal sinal tambem sera enviado para a interface Serial
  podendo ser visualizado pelo serial plotter.
    Esquema de montagem:
    Arduino - Dispositivo
    DAC0    - Sinal de saida do canal 0
    DAC1    - Sinal de saida do canal 1
    GND     - Ground comum
*/
#define PINODAC DAC0
#define UART_BAUDRATE 115200

const double ecg_wave[500] = {
  0, 0.00027337, 0.00054675, 0.00082012, 0.0010935, 0.0013669, 0.0016402, 0.0019136, 0.002187, 0.0024604, 0.0027337, 0.0030071, 0.0032805, 0.0035539, 0.0038272, 0.0041006,
0.004374, 0.0046473, 0.0049207, 0.0051941, 0.0054675, 0.0057408, 0.0060142, 0.0062876, 0.006561, 0.0068343, 0.0071077, 0.0073811, 0.0076545, 0.0079278, 0.0082012, 0.0084746,
0.017655, 0.026836, 0.036017, 0.045198, 0.054379, 0.063559, 0.07274, 0.081921, 0.091102, 0.10028, 0.10946, 0.11864, 0.12782, 0.13701, 0.14619, 0.15537,
0.16455, 0.17373, 0.18291, 0.19209, 0.20127, 0.21045, 0.21963, 0.22881, 0.23799, 0.24718, 0.25636, 0.26554, 0.27472, 0.2839, 0.29308, 0.30226,
0.31144, 0.32062, 0.3298, 0.33898, 0.3298, 0.32062, 0.31144, 0.30226, 0.29308, 0.2839, 0.27472, 0.26554, 0.25636, 0.24718, 0.23799, 0.22881,
0.21963, 0.21045, 0.20127, 0.19209, 0.18291, 0.17373, 0.16455, 0.15537, 0.14619, 0.13701, 0.12782, 0.11864, 0.10946, 0.10028, 0.091102, 0.081921,
0.07274, 0.063559, 0.054379, 0.045198, 0.036017, 0.026836, 0.017655, 0.0084746, 0.0082903, 0.0081061, 0.0079219, 0.0077377, 0.0075534, 0.0073692, 0.007185, 0.0070007,
0.0068165, 0.0066323, 0.006448, 0.0062638, 0.0060796, 0.0058954, 0.0057111, 0.0055269, 0.0053427, 0.0051584, 0.0049742, 0.00479, 0.0046057, 0.0044215, 0.0042373, 0.0040531,
0.0038688, 0.0036846, 0.0035004, 0.0033161, 0.0031319, 0.0029477, 0.0027634, 0.0025792, 0.002395, 0.0022108, 0.0020265, 0.0018423, 0.0016581, 0.0014738, 0.0012896, 0.0011054,
0.00092115, 0.00073692, 0.00055269, 0.00036846, 0.00018423, 0, -0.026194, -0.052388, -0.078582, -0.10478, -0.13097, -0.15716, -0.18336, -0.20955, -0.23575, -0.26194,
-0.28814, -0.23661, -0.18508, -0.13356, -0.082034, -0.030508, 0.021017, 0.072542, 0.12407, 0.17559, 0.22712, 0.27864, 0.33017, 0.38169, 0.43322, 0.48475,
0.53627, 0.5878, 0.63932, 0.69085, 0.74237, 0.7939, 0.84542, 0.89695, 0.94847, 1, 0.92644, 0.85288, 0.77932, 0.70576, 0.6322, 0.55864,
0.48508, 0.41153, 0.33797, 0.26441, 0.19085, 0.11729, 0.043729, -0.029831, -0.10339, -0.17695, -0.25051, -0.32407, -0.39763, -0.47119, -0.54475, -0.61831,
-0.69186, -0.76542, -0.83898, -0.76907, -0.69915, -0.62924, -0.55932, -0.48941, -0.41949, -0.34958, -0.27966, -0.20975, -0.13983, -0.069915, 0, 0.00018625,
0.00037251, 0.00055876, 0.00074502, 0.00093127, 0.0011175, 0.0013038, 0.00149, 0.0016763, 0.0018625, 0.0020488, 0.0022351, 0.0024213, 0.0026076, 0.0027938, 0.0029801, 0.0031663,
0.0033526, 0.0035388, 0.0037251, 0.0039113, 0.0040976, 0.0042839, 0.0044701, 0.0046564, 0.0048426, 0.0050289, 0.0052151, 0.0054014, 0.0055876, 0.0057739, 0.0059601, 0.0061464,
0.0063327, 0.0065189, 0.0067052, 0.0068914, 0.0070777, 0.0072639, 0.0074502, 0.0076364, 0.0078227, 0.0080089, 0.0081952, 0.0083814, 0.0085677, 0.008754, 0.0089402, 0.0091265,
0.0093127, 0.009499, 0.0096852, 0.0098715, 0.010058, 0.010244, 0.01043, 0.010617, 0.010803, 0.010989, 0.011175, 0.011362, 0.011548, 0.011734, 0.01192, 0.012107,
0.012293, 0.012479, 0.012665, 0.012852, 0.013038, 0.013224, 0.01341, 0.013597, 0.013783, 0.013969, 0.014155, 0.014342, 0.014528, 0.014714, 0.0149, 0.015087,
0.015273, 0.015459, 0.015645, 0.015832, 0.016018, 0.016204, 0.01639, 0.016577, 0.016763, 0.016949, 0.021422, 0.025895, 0.030367, 0.03484, 0.039313, 0.043785,
0.048258, 0.052731, 0.057203, 0.061676, 0.066149, 0.070621, 0.075094, 0.079567, 0.08404, 0.088512, 0.092985, 0.097458, 0.10193, 0.1064, 0.11088, 0.11535,
0.11982, 0.12429, 0.12877, 0.13324, 0.13771, 0.14218, 0.14666, 0.15113, 0.1556, 0.16008, 0.16455, 0.16902, 0.17349, 0.17797, 0.17349, 0.16902,
0.16455, 0.16008, 0.1556, 0.15113, 0.14666, 0.14218, 0.13771, 0.13324, 0.12877, 0.12429, 0.11982, 0.11535, 0.11088, 0.1064, 0.10193, 0.097458,
0.092985, 0.088512, 0.08404, 0.079567, 0.075094, 0.070621, 0.066149, 0.061676, 0.057203, 0.052731, 0.048258, 0.043785, 0.039313, 0.03484, 0.030367, 0.025895,
0.021422, 0.016949, 0.016142, 0.015335, 0.014528, 0.013721, 0.012914, 0.012107, 0.011299, 0.010492, 0.0096852, 0.0088781, 0.008071, 0.0072639, 0.0064568, 0.0056497,
0.0048426, 0.0040355, 0.0032284, 0.0024213, 0.0016142, 0.0008071, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0
};

const double sin_wave[500] = {
  0, 0.012591, 0.02518, 0.037766, 0.050345, 0.062916, 0.075477, 0.088027, 0.10056, 0.11308, 0.12558, 0.13806,
0.15052, 0.16296, 0.17537, 0.18775, 0.2001, 0.21243, 0.22471, 0.23696, 0.24918, 0.26135, 0.27348, 0.28557, 0.29762, 0.30962, 0.32156, 0.33346,
0.3453, 0.35709, 0.36883, 0.3805, 0.39212, 0.40367, 0.41515, 0.42658, 0.43793, 0.44922, 0.46043, 0.47157, 0.48264, 0.49363, 0.50454, 0.51537,
0.52612, 0.53678, 0.54736, 0.55786, 0.56826, 0.57858, 0.5888, 0.59893, 0.60897, 0.61891, 0.62875, 0.63849, 0.64813, 0.65767, 0.6671, 0.67643,
0.68565, 0.69476, 0.70376, 0.71265, 0.72143, 0.73009, 0.73863, 0.74706, 0.75537, 0.76357, 0.77164, 0.77958, 0.78741, 0.79511, 0.80268, 0.81013,
0.81744, 0.82463, 0.83169, 0.83861, 0.84541, 0.85206, 0.85859, 0.86497, 0.87122, 0.87734, 0.88331, 0.88914, 0.89483, 0.90038, 0.90579, 0.91105,
0.91617, 0.92115, 0.92597, 0.93065, 0.93519, 0.93957, 0.94381, 0.9479, 0.95183, 0.95562, 0.95925, 0.96273, 0.96606, 0.96924, 0.97226, 0.97513,
0.97784, 0.9804, 0.9828, 0.98505, 0.98714, 0.98908, 0.99085, 0.99247, 0.99394, 0.99524, 0.99639, 0.99738, 0.99821, 0.99889, 0.9994, 0.99976,
0.99996, 1, 0.99988, 0.9996, 0.99916, 0.99857, 0.99782, 0.9969, 0.99584, 0.99461, 0.99322, 0.99168, 0.98998, 0.98813, 0.98611, 0.98395,
0.98162, 0.97914, 0.9765, 0.97371, 0.97077, 0.96767, 0.96442, 0.96101, 0.95745, 0.95374, 0.94988, 0.94587, 0.94171, 0.9374, 0.93294, 0.92833,
0.92358, 0.91868, 0.91363, 0.90844, 0.9031, 0.89763, 0.892, 0.88624, 0.88034, 0.8743, 0.86812, 0.8618, 0.85534, 0.84875, 0.84203, 0.83517,
0.82818, 0.82105, 0.8138, 0.80642, 0.79891, 0.79127, 0.78351, 0.77562, 0.76762, 0.75949, 0.75123, 0.74286, 0.73438, 0.72577, 0.71705, 0.70822,
0.69927, 0.69022, 0.68105, 0.67178, 0.6624, 0.65291, 0.64332, 0.63363, 0.62384, 0.61395, 0.60396, 0.59388, 0.5837, 0.57343, 0.56307, 0.55262,
0.54208, 0.53146, 0.52075, 0.50996, 0.49909, 0.48814, 0.47711, 0.46601, 0.45483, 0.44358, 0.43226, 0.42087, 0.40942, 0.3979, 0.38632, 0.37467,
0.36297, 0.35121, 0.33939, 0.32752, 0.3156, 0.30362, 0.2916, 0.27954, 0.26742, 0.25527, 0.24308, 0.23084, 0.21857, 0.20627, 0.19393, 0.18156,
0.16917, 0.15675, 0.1443, 0.13183, 0.11933, 0.10682, 0.094296, 0.081754, 0.069198, 0.056632, 0.044056, 0.031474, 0.018886, 0.0062957, -0.0062957, -0.018886,
-0.031474, -0.044056, -0.056632, -0.069198, -0.081754, -0.094296, -0.10682, -0.11933, -0.13183, -0.1443, -0.15675, -0.16917, -0.18156, -0.19393, -0.20627, -0.21857,
-0.23084, -0.24308, -0.25527, -0.26742, -0.27954, -0.2916, -0.30362, -0.3156, -0.32752, -0.33939, -0.35121, -0.36297, -0.37467, -0.38632, -0.3979, -0.40942,
-0.42087, -0.43226, -0.44358, -0.45483, -0.46601, -0.47711, -0.48814, -0.49909, -0.50996, -0.52075, -0.53146, -0.54208, -0.55262, -0.56307, -0.57343, -0.5837,
-0.59388, -0.60396, -0.61395, -0.62384, -0.63363, -0.64332, -0.65291, -0.6624, -0.67178, -0.68105, -0.69022, -0.69927, -0.70822, -0.71705, -0.72577, -0.73438,
-0.74286, -0.75123, -0.75949, -0.76762, -0.77562, -0.78351, -0.79127, -0.79891, -0.80642, -0.8138, -0.82105, -0.82818, -0.83517, -0.84203, -0.84875, -0.85534,
-0.8618, -0.86812, -0.8743, -0.88034, -0.88624, -0.892, -0.89763, -0.9031, -0.90844, -0.91363, -0.91868, -0.92358, -0.92833, -0.93294, -0.9374, -0.94171,
-0.94587, -0.94988, -0.95374, -0.95745, -0.96101, -0.96442, -0.96767, -0.97077, -0.97371, -0.9765, -0.97914, -0.98162, -0.98395, -0.98611, -0.98813, -0.98998,
-0.99168, -0.99322, -0.99461, -0.99584, -0.9969, -0.99782, -0.99857, -0.99916, -0.9996, -0.99988, -1, -0.99996, -0.99976, -0.9994, -0.99889, -0.99821,
-0.99738, -0.99639, -0.99524, -0.99394, -0.99247, -0.99085, -0.98908, -0.98714, -0.98505, -0.9828, -0.9804, -0.97784, -0.97513, -0.97226, -0.96924, -0.96606,
-0.96273, -0.95925, -0.95562, -0.95183, -0.9479, -0.94381, -0.93957, -0.93519, -0.93065, -0.92597, -0.92115, -0.91617, -0.91105, -0.90579, -0.90038, -0.89483,
-0.88914, -0.88331, -0.87734, -0.87122, -0.86497, -0.85859, -0.85206, -0.84541, -0.83861, -0.83169, -0.82463, -0.81744, -0.81013, -0.80268, -0.79511, -0.78741,
-0.77958, -0.77164, -0.76357, -0.75537, -0.74706, -0.73863, -0.73009, -0.72143, -0.71265, -0.70376, -0.69476, -0.68565, -0.67643, -0.6671, -0.65767, -0.64813,
-0.63849, -0.62875, -0.61891, -0.60897, -0.59893, -0.5888, -0.57858, -0.56826, -0.55786, -0.54736, -0.53678, -0.52612, -0.51537, -0.50454, -0.49363, -0.48264,
-0.47157, -0.46043, -0.44922, -0.43793, -0.42658, -0.41515, -0.40367, -0.39212, -0.3805, -0.36883, -0.35709, -0.3453, -0.33346, -0.32156, -0.30962, -0.29762,
-0.28557, -0.27348, -0.26135, -0.24918, -0.23696, -0.22471, -0.21243, -0.2001, -0.18775, -0.17537, -0.16296, -0.15052, -0.13806, -0.12558, -0.11308, -0.10056,
-0.088027, -0.075477, -0.062916, -0.050345, -0.037766, -0.02518, -0.012591, -2.4493e-16
};

//Obs: A forma de onda quadrada, triangular e rampa sera gerada em tempo de execução

//Tipos de ondas possiveis de se selecionar
typedef enum {
  SIN_WAVE,
  SQUARE_WAVE,
  TRIANGLE_WAVE,
  RAMP_WAVE,
  CONST_WAVE,
  ECG_WAVE
} waveforms_t;

/////////////////////////////////////////////////
// Implementacao de um timer atraves do micros //
/////////////////////////////////////////////////
class Timer_t {
  private:
    unsigned long _actual_time;
    unsigned long _waited_time;
    bool _running;
    uint32_t _interval;

  public:
    bool elapsed;

    Timer_t(uint32_t interval = 1000) {
      _interval = interval;
      elapsed = false;
      _actual_time = micros();
      _waited_time = _actual_time + interval;
    }

    void setInterval(uint32_t interval) {
      _interval = interval;
    }

    uint32_t getInterval() {
      return _interval;
    }

    void start() {
      _running = true;
      _actual_time = millis();
      _waited_time = _actual_time + _interval;
    }

    void stop() {
      _running = false;
    }

    void wait_next() {
      elapsed = false;
    }

    void update() {
      _actual_time = micros();
      if (_running) {
        if (_actual_time >= _waited_time) {
          _waited_time = _actual_time + _interval;
          elapsed = true;
        }
      }
    }

};

/////////////////////////////////////////
//Classe para gerar as formas de onda //
////////////////////////////////////////

class SignalGenerator_t {
private:
  Timer_t _sampling_control;
  waveforms_t _waveform; //Acessible by getter and setter
  uint8_t _actual_index;
  uint8_t _pin_out;
  uint8_t _resolution_bits;
  uint16_t _max_value_resolution;
  double _actual_value;
  double _offset;
  double _amplitude;

  double get_next(){
    switch (_waveform) {
      case SIN_WAVE:
      _actual_value = sin_wave[_actual_index];
      break;
      case SQUARE_WAVE:
      _actual_index > 250? _actual_value = -1: _actual_value = 1;
      break;
      case TRIANGLE_WAVE:
      _actual_value = (double) _actual_index / 250.0;
      if(_actual_value > 1){
        _actual_value = 1 - _actual_value;
      }
      break;
      case RAMP_WAVE:
      _actual_value = (double) _actual_index / 500.0;
      break;
      case CONST_WAVE:
      _actual_value = 1;
      break;
      case ECG_WAVE:
      _actual_value = ecg_wave[_actual_index];
      break;
    }
    _actual_value = _actual_value*_amplitude + _offset;
    ++_actual_index %= 500;
    return _actual_value;
  }

  void begin() {
    pinMode(_pin_out, OUTPUT);
    analogWriteResolution(_resolution_bits);
  }

public:
  SignalGenerator_t (uint8_t pin_out = DAC0,uint8_t resolution_bits = 12){
    _pin_out = pin_out;

    _resolution_bits = resolution_bits;
    _max_value_resolution = pow(2,12) - 1;
    begin();
    _waveform = SIN_WAVE;
    _actual_index = 0;

    _sampling_control.setInterval(1000);
    _offset = 0;
    _amplitude = 100;
  }

  void start(){
    _sampling_control.start();
  }

  void stop(){
    _sampling_control.stop();
  }

  void generate_value(){
    Serial.println(get_next());
  }

  void update() {
    _sampling_control.update();
    if (_sampling_control.elapsed) {
      generate_value();
      _sampling_control.wait_next();
    }
  }

  ////////////////////////
  //Getters and Setters //
  ////////////////////////
  void setAquireInterval(uint32_t interval) {
    _sampling_control.setInterval(interval);
  }

  uint32_t getAquireInterval() {
    return _sampling_control.getInterval();
  }

  void setFreq(uint32_t frequency) {
    setAquireInterval(1000000 / frequency);
  }

  uint32_t getFreq() {
    return 1000000 / getAquireInterval();
  }

  waveforms_t getWaveform(){
    return _waveform;
  }

  void setWaveform(waveforms_t waveform){
    _waveform = waveform;
  }
};

//////////////////////
//Variaveis globais //
//////////////////////
SignalGenerator_t my_generator(); //lazy thing, work around...
bool status_led = false;
char serialOp;
//////////////////
//Main Function //
//////////////////
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(UART_BAUDRATE);
  Serial.println("Hora do show porra!");
  Serial.println("Envie um comando:");
  Serial.println("+: Gerar");
  Serial.println("p: Parar");
  Serial.println("s: Seno");
  Serial.println("r: Retangular");
  Serial.println("t: Triangular");
  Serial.println("a: Rampa");
  Serial.println("e: ECG");
  //Biiirl
  my_generator.start();
}

void loop() {
  my_generator.update();
}
//Ta bonito:
// if (Serial.available()) {
//   serialOp = Serial.read();
//   switch (serialOp) {
//     case '+':
//       motor.setFreq(motor.getFreq() + 1);
//       Serial.println("Step Freq: " + String(motor.getFreq()) + " Hz");
//       Serial.println("Step Interval: " + String(motor.getStepInterval()) + " us");
//       break;
//     case '1':
//       motor.setFreq(motor.getFreq() + 10);
//       Serial.println("Step Freq: " + String(motor.getFreq()) + " Hz");
//       Serial.println("Step Interval: " + String(motor.getStepInterval()) + " us");
//       break;
//     case '2':
//       motor.setFreq(motor.getFreq() - 10);
//       Serial.println("Step Freq: " + String(motor.getFreq()) + " Hz");
//       Serial.println("Step Interval: " + String(motor.getStepInterval()) + " us");
//       break;
//     case '3':
//       motor.setFreq(motor.getFreq() + 100);
//       Serial.println("Step Freq: " + String(motor.getFreq()) + " Hz");
//       Serial.println("Step Interval: " + String(motor.getStepInterval()) + " us");
//       break;
//     case '4':
//       motor.setFreq(motor.getFreq() - 100);
//       Serial.println("Step Freq: " + String(motor.getFreq()) + " Hz");
//       Serial.println("Step Interval: " + String(motor.getStepInterval()) + " us");
//       break;
//     case '-':
//       motor.setFreq(motor.getFreq() - 1);
//       Serial.println("Step Freq: " + String(motor.getFreq()) + " Hz");
//       Serial.println("Step Interval: " + String(motor.getStepInterval()) + " us");
//       break;
//
//     case 'p':
//       motor.stop();
//       Serial.println("Stopped");
//       break;
//     case 'r':
//       motor.rotateClockwise();
//       Serial.println("Started Clockwise");
//       break;
//     case 'a':
//       motor.rotateAntiClockwise();
//       Serial.println("Started AntiClockwise");
//       break;
//     case 's':
//       motor.setAcionamento(SINGLE_STEP);
//       Serial.println("Mode: Single-Step");
//       break;
//     case 'd':
//       motor.setAcionamento(DOUBLE_STEP);
//       Serial.println("Mode: Double-Step");
//       break;
//     case 'h':
//       motor.setAcionamento(HALF_STEP);
//       Serial.println("Mode: Half-Step");
//       break;
//     default:
//       break;
//   }