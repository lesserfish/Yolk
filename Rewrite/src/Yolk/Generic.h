namespace Yolk {

    class UUID {
        public:
            static UUID New();
            unsigned long long int value;
        private:
            UUID();
            UUID(UUID&);
    };
}
