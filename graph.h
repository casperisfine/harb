#ifndef HARB_GRAPH_H
#define HARB_GRAPH_H

#include <inttypes.h>

#include "sparsepp/spp.h"

#include "parser.h"
#include "ruby_heap_obj.h"
#include "dominator_tree.h"

namespace harb {

class Graph {
  typedef spp::sparse_hash_map<uint64_t, RubyHeapObj *> RubyHeapObjMap;

  Parser *parser_;
  RubyHeapObj *root_;
  RubyHeapObjMap heap_map_;
  DominatorTree *dominator_tree_;

  void add_inverse_obj_references(RubyHeapObj *obj);
  void update_obj_references(RubyHeapObj *obj);
  void update_references();
  void build_dominator_tree();

public:
  Graph(FILE *f);

  RubyHeapObj* get_heap_object(uint64_t addr);

  RubyHeapObj* get_idom(RubyHeapObj *obj) {
    return dominator_tree_->get_idom(obj);
  }

  void get_dominators(RubyHeapObj *obj, std::vector<RubyHeapObj *> &dominators) {
    return dominator_tree_->get_dominators(obj, dominators);
  }

  size_t get_retained_size(RubyHeapObj *obj) {
    size_t size = 0;
    dominator_tree_->retained_size(obj, size);
    return size;
  }

  size_t get_num_heap_objects() { return heap_map_.size(); }

  template<typename Func> void each_heap_object(Func func) {
    for (auto obj: heap_map_) { func(obj.second); }
  }
};

}

#endif // HARB_GRAPH_H
