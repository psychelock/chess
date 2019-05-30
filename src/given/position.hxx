namespace board
{
    inline Position::Position(File file, Rank rank)
        : file_(file)
        , rank_(rank)
    {}

    inline bool Position::operator==(const Position& pos) const
    {
        return file_get() == pos.file_get() && rank_get() == pos.rank_get();
    }

    inline bool Position::operator!=(const Position& pos) const
    {
        return !(*this == pos);
    }

    inline File Position::file_get() const
    {
        return file_;
    }

    inline Rank Position::rank_get() const
    {
        return rank_;
    }

    inline char get_file(File f)
    {
        switch (f)
        {
            case File::A:
                return 'A';
            case File::B:
                return 'B';
            case File::C:
                return 'C';
            case File::D:
                return 'D';
            case File::E:
                return 'E';
            case File::F:
                return 'F';
            case File::G:
                return 'G';
            default:
                return 'H';
        }
    }
} // namespace board
