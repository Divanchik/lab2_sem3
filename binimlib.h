/**
 * \file
 * Binary Image library (header file)
 */
#pragma once
namespace binim
{
    /// Enable/disable logging
    static bool trace;
    /// Enable logging
    void enable_logging();
    /// Disable logging
    void disable_logging();
    /**
     * Print message if logging enabled
     * \param[in] s Message
     */
    void log(const char *s);
    /// \return Length of string.
    int strlen(const char *s);
    /**
     * \param[in] s String
     * \param[in] c Character that you want to find
     * \return Index of char in string or '-1' if NOT found
     */
    int find_char(const char c, const char *s);
    /**
     * Safe integer input
     * \param[out] a Integer
     * \param[in] s Message
     */
    void int_input(int &a, const char *s);
    /**
     * \param[in] s String
     * \param[in] c Character that you want to count
     * \return Amount of char in string
     */
    int count_char(const char c, const char *s);
    /// \return True if 'n' is in interval ['a', 'b']
    int int_in(const int n, const int a, const int b);
    /// Binary image class
    class BinImage
    {
        
        bool **f; ///< Image array
        int n; ///< Height of image
        int m; ///< Width of image
        bool is_image_changed; ///< Cache for amount of 'true' values
        double cache_coefficient; ///< Cache for coefficient

        /// Free image array
        void delete_f();

        /// Create image array
        void create_f(int a, int b);

    public:
        /// \return Amount of true values in image
        int count_true() const;
        /**
         * Fill image with some value
         * \param[in] fill Fill value
         */
        void fill_value(const bool fill);
        /**
         * Set height and width of image
         * \param[in] new_height New height of image
         * \param[in] new_width New width of image
         */
        void resize(int new_height, int new_width);
        /// \return Height of image
        int _n() const;
        /// \return Width of image
        int _m() const;
        /// \return 'true' if image is changed
        bool _is_image_changed() const;
        /// \return 'true' if size of image is defined
        bool _is_created() const;
        /// \return Cached coefficient
        double _cache() const;
        /// Input method
        void input();
        /// Output method
        void output() const;
        /// Default constructor
        BinImage();
        /// Constructor, defining size and filling image with some value
        BinImage(const int a, const int b, const int fill);
        /// Copy constructor
        BinImage(const BinImage &b);
        /// Move constructor
        BinImage(BinImage &&b);
        /// Destructor
        ~BinImage();

        // Operators overload

        /**
         * Access operator
         * \param[in] a Height of element
         * \param[in] b Width of element
         * \return Element of image with ('a', 'b') coordinates
         */
        bool& operator()(const int a, const int b);
        /**
         * Access operator
         * \param[in] a Height of element
         * \param[in] b Width of element
         * \return Element of image with ('a', 'b') coordinates
         */
        bool operator()(const int a, const int b) const;
        /// \return Inverted image
        BinImage operator!();
        /// \return Coefficient (amount of true value in image divided by amount of all elements in image)
        double coefficient();
        /// Copy assignment operator overload
        BinImage &operator=(const BinImage &b);
        /// Move assignment operator overload
        BinImage &operator=(BinImage &&b);
    };
    /// Output operator overload
    std::ostream &operator<<(std::ostream &os, const BinImage &a);
    /**
     * Fill image with random values
     * \param[out] a Binary image
     */
    void fill_random(BinImage &a);
    /** 
     * Operator overload.
     * \return Image * value
     */
    BinImage operator*(const BinImage &a, const BinImage &b);
    /** 
     * Operator overload.
     * \return Image + image
     */
    BinImage operator+(const BinImage &a, const BinImage &b);
    /** 
     * Operator overload.
     * \return Image * value
     */
    BinImage operator*(const BinImage &a, const int l);
    /** 
     * Operator overload.
     * \return Image + value
     */
    BinImage operator+(const BinImage &a, const int l);
    /** 
     * Operator overload.
     * \return Image * value
     */
    BinImage operator*(const int l, const BinImage &b);
    /** 
     * Operator overload.
     * \return Image + value
     */
    BinImage operator+(const int l, const BinImage &b);
};