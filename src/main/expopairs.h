#ifndef SHUTTERS_TABLE
  #define SHUTTERS_TABLE
    class Expopair
    {
      public:
        Expopair();
        int aperture_value(int index);
        int shutter_speed(int index);
        int status();
        char status_str();
        int amount_pairs();
        void update(float ev);
      private:
        int _first_shutter_speed_index;
        int _first_aperture_index;
        int _status;
        int _amount_pairs;
    };

#endif
