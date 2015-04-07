<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:strip-space elements="*" />
<!-- Import the identity transformation. -->

 <!--
   <xsl:import href="Identity.xsl"/>
  -->
   <xsl:template match="node()|@*">
    <xsl:copy>
      <xsl:apply-templates select="@*|node()"/>
    </xsl:copy>
  </xsl:template>


    <!-- Mark question as deleted /ssn/p[@idx='27']/. -->
  <xsl:template match="ssn/p/v">
    <xsl:if test="@att = 1"> 
      <xsl:copy-of select="." /> 
      
    </xsl:if>
  </xsl:template>
</xsl:stylesheet>
