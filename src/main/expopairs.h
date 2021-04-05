#ifndef SHUTTERS_TABLE
  #define SHUTTERS_TABLE
    class Expopair
    {
      public:
        Expopair();
        int aperture_value(int index);
        int shutter_speed(int index);
        int status();
        uint8_t amount_pairs();
        void update(int ev_x100);
      private:
        uint8_t _first_shutter_speed_index;
        uint8_t _first_aperture_index;
        int _status;
        uint8_t _amount_pairs;
    };

#endif
