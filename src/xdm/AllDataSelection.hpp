#ifndef xdm_AllDataSelection_hpp
#define xdm_AllDataSelection_hpp

#include <xdm/DataSelection.hpp>
#include <xdm/DataSelectionVisitor.hpp>

#include <xdm/NamespaceMacro.hpp>

XDM_NAMESPACE_BEGIN

/// DataSelection that simply selects all data.
class AllDataSelection : public DataSelection {
public:
  AllDataSelection() {}
  virtual ~AllDataSelection() {}
  virtual void accept( DataSelectionVisitor& v ) const { v.apply(*this); }
};

XDM_NAMESPACE_END

#endif // xdm_AllDataSelection_hpp
