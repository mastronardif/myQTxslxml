<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!-- Import the identity transformation. -->
 <xsl:import href="Identity.xsl"/>
 <!--
   <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="@*|node()"/>
    </xsl:copy>
  </xsl:template>
-->

    <!-- Mark question as deleted /ssn/p[@idx='27']/. -->
  <xsl:template match="ssn/p[@idx='27']/@isDel">
      <xsl:attribute name="isDel">
       <xsl:value-of select="'fm-N'"/>
     </xsl:attribute>
  </xsl:template>

  <xsl:template match="ssn/p[@idx='28']/@isDel">
      <xsl:attribute name="isDel">
       <xsl:value-of select="'fm-Y'"/>
     </xsl:attribute>
  </xsl:template>

<!-- if not there lets add the attrib -->
<xsl:template match="ssn/p[@idx='26']">

<p isDel="fn-Y">
   <xsl:apply-templates select="@*|node()"/>
  </p>

<!--
    <xsl:attribute name="isDel">
     <xsl:value-of select="'fm-Y'"/>
   </xsl:attribute>
   -->
</xsl:template>

  <xsl:template match="@nm">
     <xsl:attribute name="n">
       <xsl:value-of select="concat('new',.)"/>
     </xsl:attribute>
  </xsl:template>
</xsl:stylesheet>
