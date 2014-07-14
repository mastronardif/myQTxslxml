<?xml version="1.0" encoding="utf-8"?>
<!--
File: _______
Purpose: Used for marking question for delete/undelete.
see xslt for details.
-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- Import the identity transformation.
<xsl:import href="Identity.xsl"/>
-->

   <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="@*|node()"/>
    </xsl:copy>
  </xsl:template>

<!-- if not there lets add the attrib -->
<!-- Mark question as _____ by /ssn/p[@idx='27']/. -->
<xsl:template match="__XP_FIND_Q_BY_IDX__">
<p isDel="__ISDEL_ACTION__">
   <xsl:apply-templates select="@*|node()"/>
  </p>
</xsl:template>
</xsl:stylesheet>
