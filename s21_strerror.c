#include "s21_string.h"

char *s21_strerror(int errnum) {
#ifdef __linux__
  static char messeges[][108] = {
      "Success",
      "Operation not permitted",
      "No such file or directory",
      "No such process",
      "Interrupted system call",
      "Input/output error",
      "No such device or address",
      "Argument list too long",
      "Exec format error",
      "Bad file descriptor",
      "No child processes",
      "Resource temporarily unavailable",
      "Cannot allocate memory",
      "Permission denied",
      "Bad address",
      "Block device required",
      "Device or resource busy",
      "File exists",
      "Invalid cross-device link",
      "No such device",
      "Not a directory",
      "Is a directory",
      "Invalid argument",
      "Too many open files in system",
      "Too many open files",
      "Inappropriate ioctl for device",
      "Text file busy",
      "File too large",
      "No space left on device",
      "Illegal seek",
      "Read-only file system",
      "Too many links",
      "Broken pipe",
      "Numerical argument out of domain",
      "Numerical result out of range",
      "Resource deadlock avoided",
      "File name too long",
      "No locks available",
      "Function not implemented",
      "Directory not empty",
      "Too many levels of symbolic links",
      "Unknown error 41",
      "No message of desired type",
      "Identifier removed",
      "Channel number out of range",
      "Level 2 not synchronized",
      "Level 3 halted",
      "Level 3 reset",
      "Link number out of range",
      "Protocol driver not attached",
      "No CSI structure available",
      "Level 2 halted",
      "Invalid exchange",
      "Invalid request descriptor",
      "Exchange full",
      "No anode",
      "Invalid request code",
      "Invalid slot",
      "Unknown error 58",
      "Bad font file format",
      "Device not a stream",
      "No data available",
      "Timer expired",
      "Out of streams resources",
      "Machine is not on the network",
      "Package not installed",
      "Object is remote",
      "Link has been severed",
      "Advertise error",
      "Srmount error",
      "Communication error on send",
      "Protocol error",
      "Multihop attempted",
      "RFS specific error",
      "Bad message",
      "Value too large for defined data type",
      "Name not unique on network",
      "File descriptor in bad state",
      "Remote address changed",
      "Can not access a needed shared library",
      "Accessing a corrupted shared library",
      ".lib section in a.out corrupted",
      "Attempting to link in too many shared libraries",
      "Cannot exec a shared library directly",
      "Invalid or incomplete multibyte or wide character",
      "Interrupted system call should be restarted",
      "Streams pipe error",
      "Too many users",
      "Socket operation on non-socket",
      "Destination address required",
      "Message too long",
      "Protocol wrong type for socket",
      "Protocol not available",
      "Protocol not supported",
      "Socket type not supported",
      "Operation not supported",
      "Protocol family not supported",
      "Address family not supported by protocol",
      "Address already in use",
      "Cannot assign requested address",
      "Network is down",
      "Network is unreachable",
      "Network dropped connection on reset",
      "Software caused connection abort",
      "Connection reset by peer",
      "No buffer space available",
      "Transport endpoint is already connected",
      "Transport endpoint is not connected",
      "Cannot send after transport endpoint shutdown",
      "Too many references: cannot splice",
      "Connection timed out",
      "Connection refused",
      "Host is down",
      "No route to host",
      "Operation already in progress",
      "Operation now in progress",
      "Stale file handle",
      "Structure needs cleaning",
      "Not a XENIX named type file",
      "No XENIX semaphores available",
      "Is a named type file",
      "Remote I/O error",
      "Disk quota exceeded",
      "No medium found",
      "Wrong medium type",
      "Operation canceled",
      "Required key not available",
      "Key has expired",
      "Key has been revoked",
      "Key was rejected by service",
      "Owner died",
      "State not recoverable",
      "Operation not possible due to RF-kill",
      "Memory page has hardware error",
      "Unknown error"};
  static s21_size_t num_err = sizeof(messeges) / sizeof(*messeges);
#elif defined(__APPLE__)
  static char messeges[135][108] = {
      "No error",                                   // 0
      "Operation not permitted",                    // 1 (EPERM)
      "No such file or directory",                  // 2 (ENOENT)
      "No such process",                            // 3 (ESRCH)
      "Interrupted system call",                    // 4 (EINTR)
      "Input/output error",                         // 5 (EIO)
      "Device not configured",                      // 6 (ENXIO)
      "Argument list too long",                     // 7 (E2BIG)
      "Exec format error",                          // 8 (ENOEXEC)
      "Bad file descriptor",                        // 9 (EBADF)
      "No child processes",                         // 10 (ECHILD)
      "Resource deadlock avoided",                  // 11 (EDEADLK)
      "Cannot allocate memory",                     // 12 (ENOMEM)
      "Permission denied",                          // 13 (EACCES)
      "Bad address",                                // 14 (EFAULT)
      "Block device required",                      // 15 (ENOTBLK)
      "Device / Resource busy",                     // 16 (EBUSY)
      "File exists",                                // 17 (EEXIST)
      "Cross-device link",                          // 18 (EXDEV)
      "Operation not supported by device",          // 19 (ENODEV)
      "Not a directory",                            // 20 (ENOTDIR)
      "Is a directory",                             // 21 (EISDIR)
      "Invalid argument",                           // 22 (EINVAL)
      "Too many open files in system",              // 23 (ENFILE)
      "Too many open files",                        // 24 (EMFILE)
      "Inappropriate ioctl for device",             // 25 (ENOTTY)
      "Text file busy",                             // 26 (ETXTBSY)
      "File too large",                             // 27 (EFBIG)
      "No space left on device",                    // 28 (ENOSPC)
      "Illegal seek",                               // 29 (ESPIPE)
      "Read-only file system",                      // 30 (EROFS)
      "Too many links",                             // 31 (EMLINK)
      "Broken pipe",                                // 32 (EPIPE)
      "Numerical argument out of domain",           // 33 (EDOM)
      "Result too large",                           // 34 (ERANGE)
      "Resource temporarily unavailable",           // 35 (EAGAIN)
      "Operation would block",                      // 35 (EWOULDBLOCK)
      "Operation now in progress",                  // 36 (EINPROGRESS)
      "Operation already in progress",              // 37 (EALREADY)
      "Socket operation on non-socket",             // 38 (ENOTSOCK)
      "Destination address required",               // 39 (EDESTADDRREQ)
      "Message too long",                           // 40 (EMSGSIZE)
      "Protocol wrong type for socket",             // 41 (EPROTOTYPE)
      "Protocol not available",                     // 42 (ENOPROTOOPT)
      "Protocol not supported",                     // 43 (EPROTONOSUPPORT)
      "Socket type not supported",                  // 44 (ESOCKTNOSUPPORT)
      "Operation not supported on socket",          // 45 (EOPNOTSUPP)
      "Protocol family not supported",              // 46 (EPFNOSUPPORT)
      "Address family not supported by protocol",   // 47 (EAFNOSUPPORT)
      "Address already in use",                     // 48 (EADDRINUSE)
      "Can't assign requested address",             // 49 (EADDRNOTAVAIL)
      "Network is down",                            // 50 (ENETDOWN)
      "Network is unreachable",                     // 51 (ENETUNREACH)
      "Network dropped connection on reset",        // 52 (ENETRESET)
      "Software caused connection abort",           // 53 (ECONNABORTED)
      "Connection reset by peer",                   // 54 (ECONNRESET)
      "No buffer space available",                  // 55 (ENOBUFS)
      "Socket is already connected",                // 56 (EISCONN)
      "Socket is not connected",                    // 57 (ENOTCONN)
      "Can't send after socket shutdown",           // 58 (ESHUTDOWN)
      "Too many references: can't splice",          // 59 (ETOOMANYREFS)
      "Operation timed out",                        // 60 (ETIMEDOUT)
      "Connection refused",                         // 61 (ECONNREFUSED)
      "Too many levels of symbolic links",          // 62 (ELOOP)
      "File name too long",                         // 63 (ENAMETOOLONG)
      "Host is down",                               // 64 (EHOSTDOWN)
      "No route to host",                           // 65 (EHOSTUNREACH)
      "Directory not empty",                        // 66 (ENOTEMPTY)
      "Too many processes",                         // 67 (EPROCLIM)
      "Too many users",                             // 68 (EUSERS)
      "Disc quota exceeded",                        // 69 (EDQUOT)
      "Stale NFS file handle",                      // 70 (ESTALE)
      "Too many levels of remote in path",          // 71 (EREMOTE)
      "RPC struct is bad",                          // 72 (EBADRPC)
      "RPC version wrong",                          // 73 (ERPCMISMATCH)
      "RPC program not available",                  // 74 (EPROGUNAVAIL)
      "RPC program version wrong",                  // 75 (EPROGMISMATCH)
      "RPC procedure unavailable",                  // 76 (EPROCUNAVAIL)
      "No locks available",                         // 77 (ENOLCK)
      "Function not implemented",                   // 78 (ENOSYS)
      "Inappropriate file type or format",          // 79 (EFTYPE)
      "Authentication error",                       // 80 (EAUTH)
      "Need authenticator",                         // 81 (ENEEDAUTH)
      "Device power is off",                        // 82 (EPWROFF)
      "Device error",                               // 83 (EDEVERR)
      "Value too large to be stored in data type",  // 84 (EOVERFLOW)
      "Bad executable (or shared library)",         // 85 (EBADEXEC)
      "Bad CPU type in executable",                 // 86 (EBADARCH)
      "Shared library version mismatch",            // 87 (ESHLIBVERS)
      "Malformed Mach-o file",                      // 88 (EBADMACHO)
      "Operation canceled",                         // 89 (ECANCELED)
      "Identifier removed",                         // 90 (EIDRM)
      "No message of desired type",                 // 91 (ENOMSG)
      "Illegal byte sequence",                      // 92 (EILSEQ)
      "Attribute not found",                        // 93 (ENOATTR)
      "Bad message",                                // 94 (EBADMSG)
      "No message available on STREAM",             // 96 (ENODATA)
      "Not a STREAM",                               // 99 (ENOSTR)
      "Protocol error",                             // 100 (EPROTO)
      "STREAM ioctl timeout",                       // 101 (ETIME)
      "Operation canceled",                         // 102 (EOPCANCELLED)
      "Previous owner died",                        // 105 (EOWNERDEAD)
      "State not recoverable",                      // 106 (ENOTRECOVERABLE)
      "Unknown error"};
  static s21_size_t num_err = sizeof(messeges) / sizeof(*messeges);
#endif

  int index = num_err - 1;
  if (errnum >= 0 && errnum < index) {
    index = errnum;
  } else {
    s21_sprintf((char *)messeges[index] + 13, " %d", errnum);
  }
  return (char *)messeges[index];
}
