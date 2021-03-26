#ifndef OLED_MONITOR
  #define OLED_MONITOR
    class OledMonitor
    {
        public:
            OledMonitor();
            void setup();
            void render();
            void set_iso(int iso);
            void set_top_av(int top_av);
            void set_top_t(int top_t);
            void set_main_av(int main_av);
            void set_main_t(int main_t);
            void set_bottom_av(int bottom_av);
            void set_bottom_t(int bottom_t);
            void set_ev(float ev);
            void set_status_str(String status_str);
        private:
            int _iso;
            int _top_av;
            int _top_t;
            int _main_av;
            int _main_t;
            int _bottom_av;
            int _bottom_t;
            float _ev;
            String _status_str;
    };

#endif
