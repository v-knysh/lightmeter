#ifndef SHUTTERS_TABLE
  #define SHUTTERS_TABLE
    class ShutterAperturePair
    {
      public:
        ShutterAperturePair();
        int aperture_value(int index);
        int shutter_speed(int index);
        int status();
        int amount_pairs();
        void update(int ev);
      private:
        int _first_shutter_speed_index;
        int _first_aperture_index;
        int _status;
        int _amount_pairs;
    };

#endif
