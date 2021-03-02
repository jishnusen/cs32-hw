void listAll(const File* f, string path)  // two-parameter overload
{
  if (f == nullptr) {
    cout << path << endl;
    return;
  }
  path += "/" + f->name();
  auto vec = f->files();
  if (vec == nullptr) {
    listAll(nullptr, path);
    return;
  }
  cout << path << endl;
  for (auto it = vec->begin(); it != vec->end(); it++) {
    listAll(*it, path);
  }
}
