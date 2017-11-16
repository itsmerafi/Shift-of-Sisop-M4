#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

static const char *dirpath = "/home/droppledev/Documents";

static int xmp_getattr(const char *path, struct stat *stbuf)
{
    char filepath[500];
    int res1308;
    sprintf(filepath,"%s%s",dirpath,path);
    res1308 = lstat(filepath, stbuf);
    if(res1308 == -1){
        return -errno;
    }

    return 0;
}
static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,off_t offset, struct fuse_file_info *fi)
{
    char filepath[500];
    if(strcmp(path,"/") == 0){
        path=dirpath;
        sprintf(filepath,"%s",path);
    }
    else sprintf(filepath, "%s%s",dirpath,path);
    DIR *dp;
    struct dirent *de;

    (void) offset;
    (void) fi;

    dp = opendir(filepath);
    if (dp == NULL)
        return -errno;

    while ((de = readdir(dp)) != NULL) {
        struct stat st;
        memset(&st, 0, sizeof(st));
        st.st_ino = de->d_ino;
        st.st_mode = de->d_type << 12;
        if (filler(buf, de->d_name, &st, 0))
            break;
        }
                                          
        closedir(dp);
        return 0;
}
