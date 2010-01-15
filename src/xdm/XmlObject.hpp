#ifndef xdm_XmlObject_hpp
#define xdm_XmlObject_hpp

#include <xdm/ReferencedObject.hpp>
#include <xdm/RefPtr.hpp>

#include <list>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include <xdm/NamespaceMacro.hpp>

XDM_NAMESPACE_BEGIN

/// Interface for constructing XML data.  This class exposes simple methods for
/// constructing an XML tree on the fly. It is designed so that the XML output
/// process may be customized by client applications depending on their needs.
class XmlObject : public ReferencedObject {
private:
  std::string mTag;
  typedef std::map< std::string, std::string > AttributeMap;
  AttributeMap mAttributeMap;
  typedef std::vector< std::string > TextContent;
  TextContent mTextContent;
  typedef std::vector< RefPtr< XmlObject > > ChildList;
  ChildList mChildren;

public:
  /// Construct an XmlObject with no tag.
  XmlObject();
  /// Construct an XmlObject with the given tag.
  explicit XmlObject( const std::string& tag );
  virtual ~XmlObject();

  //-- Methods for constructing an XML tree --//
  /// Set the tag for the Object.
  void setTag( const std::string& tag );

  /// Set the attribute with the given name to the given value.  If the
  /// attribute already exists in the XmlObject, it will be overwritten.
  void appendAttribute( const std::string& name, const std::string& value );
  
  /// Append a line of text content to the XmlObject's text.
  void appendContent( const std::string& text );
  
  /// Append another XmlObject as a child of this object.
  void appendChild( XmlObject* child );

  //-- Methods for querying an XML object --//

  /// Get the tag name for this object.
  const std::string& tag() const;

  /// Determine if the object has the specified attribute.
  bool hasAttribute( const std::string& key ) const;

  /// Get the value of the specified attribute.
  const std::string& attribute( const std::string& key ) const;

  /// Get the numbered line of text content.
  const std::string& contentLine( unsigned int line ) const;

  //-- Methods for outputting an XML object --//

  /// Print the header for the XML object to an ostream.  This is the content
  /// between the <...> of the XML object.
  void printHeader( std::ostream& ostr, int indentLevel = 0 ) const;
  
  /// Print the body of the XML object (including the full body of all of it's
  /// children) to an ostream.
  void printBody( std::ostream& ostr, int indentLevel = 0 ) const;

  /// Print the footer of the XML object to an ostream.
  void printFooter( std::ostream& ostr, int indentLevel = 0 ) const;

};

/// Helper function for adding a non-string value as an attribute to an XML
/// object.  This function should succeed as long as the input type has the
/// stream insertion operator overloaded.
template< typename T >
void appendAttribute( XmlObject& obj, const std::string& name, const T& value ) {
  std::stringstream ss;
  ss << value;
  obj.appendAttribute( name, ss.str() );
}

/// Non-member function to write an xml object at a given indent level.
std::ostream& writeIndent( std::ostream& ostr, const XmlObject& obj, 
  int indentLevel );

/// Stream insertion operator for an XmlObject.
std::ostream& operator<<( std::ostream& ostr, const XmlObject& obj );

XDM_NAMESPACE_END

#endif // xdm_XmlObject_hpp
