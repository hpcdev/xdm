//=============================================================================
// This software developed by Stellar Science Ltd Co and the U.S. Government.
// Copyright (C) 2009 Stellar Science. Government-purpose rights granted.
//-----------------------------------------------------------------------------
#include <xdmf/XmfReader.hpp>

#include <xdm/Item.hpp>
#include <xdm/RefPtr.hpp>

#include <libxml/parser.h>
#include <libxml/tree.h>

XDMF_NAMESPACE_BEGIN

class XmfReader::Private {
public:
  xmlDocPtr mDocument;

  Private() :
    mDocument( 0 ) {
  }

  ~Private() {
    xmlFreeDoc( mDocument );
  }
};

XmfReader::XmfReader() {
}

XmfReader::~XmfReader() {
}

xdm::RefPtr< xdm::Item > readItem( const std::string& filename ) {
  return xdm::RefPtr< xdm::Item >();
}

XDMF_NAMESPACE_END