#ifndef OLED_MONITOR
  #define OLED_MONITOR
    class OledMonitor
    {
        public:
            OledMonitor();
            void setup();
            void update(int i);
        private:
            int _iso;
            int ev;

    };

#endif
