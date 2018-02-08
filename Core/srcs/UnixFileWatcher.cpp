//
// Created by marmus_a on 08/02/18.
//

#include "UnixFileWatcher.hpp"

UnixFileWatcher::UnixFileWatcher(const std::string &fileToWatch) {
    this->inotifyDescriptor = ::inotify_init();
    if (this->inotifyDescriptor == -1) {
        perror("inotify");
    }
    this->watchDescriptor = inotify_add_watch(this->inotifyDescriptor, fileToWatch.c_str(), IN_MODIFY | IN_MOVE_SELF | IN_MOVED_FROM);
    if (this->watchDescriptor == -1) {
        perror("FileWatcher");
    }
}

UnixFileWatcher::UnixFileWatcher() {

}

UnixFileWatcher::~UnixFileWatcher() {
    ::inotify_rm_watch(this->inotifyDescriptor, this->watchDescriptor);
    ::close(this->inotifyDescriptor);
}

void UnixFileWatcher::waitForModification() {
    char buff[this->BUFFLEN];

    read(this->inotifyDescriptor, buff, this->BUFFLEN);
}
