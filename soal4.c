#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/statfs.h>
#include <sys/types.h>
#include <sys/stat.h>

static const char *dirpath = "/home/droppledev/Downloads";

static int fuso_getattr(const char *path, struct stat *stbuf)
{
    int res1913;
    char filepath[500];
    sprintf(filepath,"%s%s",dirpath,path);
    res1913 = lstat(filepath, stbuf);

    if(res1913 == -1)
    {
        return -errno;
    }

    return 0;
}

static int fuso_chmod(const char *path, mode_t mode)
{
    int res1913;
    char filepath[500];
    char directorii[] = "/home/droppledev/Downloads/simpanan";
    sprintf(filepath,"%s%s", directorii, path);
    res1913 = chmod(filepath, mode);
    if(res1913 == -1)
        return -errno;

    return 0;
}

static int fuso_chown(const char *path, uid_t uid, gid_t gid)
{
    int res1913;
    char filepath[500];
    sprintf(filepath,"%s%s", dirpath, path);
    res1913 = lchown(filepath, uid, gid);
    if(res1913 == -1)
        return -errno;

    return 0;
}

static int fuso_getdir(const char *path, fuse_dirh_t h, fuse_dirfil_t filler)
{
    char filepath[500];
    if(strcmp(path,"/") == 0)
    {
        path=dirpath;
        sprintf(filepath,"%s",path);
    }
    else sprintf(filepath, "%s%s",dirpath,path);
    int res1913 = 0;
    DIR *dp;
    struct dirent *de;
    dp = opendir(filepath);
    if(dp==NULL){
        return -errno;
    }
    while((de = readdir(dp))!=NULL){
        res1913 = filler(h, de->d_name, de->d_type);
        if(res1913!=0) break;
    }
    closedir(dp);
    return res1913;
}

static int fuso_mkdir(const char *path,mode_t mode)
{
    int res1913;
    char filepath[500];
    sprintf(filepath,"%s%s",dirpath,path);
    res1913 = mkdir (filepath,mode);
    if(res1913 == -1)
        return -errno;
    return 0;
}

static int fuso_symlink(const char *from, const char *to)
{
    int res1913;
    char ffrom[500];
    char fto[500];
    sprintf(ffrom,"%s%s",dirpath,from);
    sprintf(fto,"%s%s",dirpath,to);
    res1913 = symlink(ffrom, fto);
    if(res1913 == -1)
        return -errno;

    return 0;
}

static int fuso_unlink(const char *path)
{
    int res1913;
    char filepath[500];
    sprintf(filepath,"%s%s", dirpath, path);
    res1913 = unlink(filepath);
    if(res1913 == -1)
        return -errno;

    return 0;
}

static int fuso_truncate(const char *path, off_t size)
{
    int res1913;
    char filepath[500];
    sprintf(filepath,"%s%s", dirpath, path);
    res1913 = truncate(filepath, size);
    if(res1913 == -1)
        return -errno;

    return 0;
}

static int fuso_mknod(const char *path, mode_t mode, dev_t rdev)
{
    int res1913;
    char filepath[500];
    sprintf(filepath,"%s%s", dirpath, path);
    res1913 = mknod(filepath, mode, rdev);
    if(res1913 == -1)
        return -errno;

    return 0;
}
