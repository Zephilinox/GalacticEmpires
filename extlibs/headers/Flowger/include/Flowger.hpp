#ifndef FLOWGER_H
#define FLOWGER_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


enum log_type
{
    FGR_DEBUG,
    FGR_WARNING,
    FGR_ERROR
};

enum print_flag
{
    PRINT_DATE          = 1,
    PRINT_TIME          = 1 << 1,
    PRINT_FILENAME      = 1 << 2,
    PRINT_LINE          = 1 << 3
};

struct info
{
    const char* date;
    const char* time;
    const char* file;
    const int line;
};

static FILE* file;

static const char* log_type_to_str(log_type type);
static bool flag_set(int flags, print_flag flag);

/*
 * Opens the file in append mode ready for writing, therefore this function
 * must be called before any logging.
 * Returns true on success and false on failure.
 */
bool fgr_init(const char* filename)
{
    file = fopen(filename, "a");
    return (file != NULL);
}

/*
 * Closes the file. This should be called when logging is no longer needed.
 * Returns true on success and false on failure.
 */
bool fgr_close()
{
    return (fclose(file) == 0);
}

#define fgr_log(message, type, flags) _fgr_log((message), { __DATE__, __TIME__, __FILE__, __LINE__ }, (type), (flags))

/*
 * This function is not called directly. Instead, the macro fgr_log should be used, which 
 * calls this function.
 *
 * The default type is DEBUG and the default behavior is to print the filename in which
 * this function was called and the line on which it was called.
 * Returns true on success and false on failure.
 */
static bool _fgr_log(const char* message, const struct info inf, log_type type = FGR_DEBUG, int flags = PRINT_FILENAME | PRINT_LINE)
{
    if (flags == 0)
    {
        return fprintf(file, "[%s] %s\n", log_type_to_str(type), message) > 0;
    }

    int num_chars_written = 0;
    num_chars_written += fprintf(file, "[%s -", log_type_to_str(type));

    if (flag_set(flags, PRINT_DATE))
    {
        num_chars_written += fprintf(file, " %s", inf.date);
    }

    if (flag_set(flags, PRINT_TIME))
    {
        num_chars_written += fprintf(file, " %s", inf.time);
    }

    if (flag_set(flags, PRINT_FILENAME))
    {
        num_chars_written += fprintf(file, " %s", inf.file);
    }

    if (flag_set(flags, PRINT_LINE))
    {
        num_chars_written += fprintf(file, " line %d", inf.line);
    }

    fprintf(file, "] %s\n", message);

    return num_chars_written > 0;
}

static const char* log_type_to_str(log_type type)
{
    switch (type)
    {
        case FGR_DEBUG:
            return "debug";
        case FGR_WARNING:
            return "warning";
        case FGR_ERROR:
            return "error";
        default:
            return "unimplemented type";
    }
}

static bool flag_set(int flags, print_flag flag)
{
    return (flags & flag) == flag;
}

#endif
