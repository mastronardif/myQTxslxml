<xsl:stylesheet
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:str="http://exslt.org/strings"
	extension-element-prefixes='str'
>
	<xsl:output method="xml" omit-xml-declaration="yes"/>

	<!-- break into rows -->
	<xsl:variable name='rows' select='str:split(root, "&#xA;")' />

	<!-- root - kick things off -->
	<xsl:template match='/'>
		<root>
			<xsl:apply-templates select='$rows' mode='row' />
		</root>
	</xsl:template>

	<!-- rows -->
	<xsl:template match='token' mode='row'>
		<xsl:variable name='cols' select='str:split(., ",")' />
		<row>
			<xsl:apply-templates select='$cols' mode='col' />
		</row>
	</xsl:template>

	<!-- columns -->
	<xsl:template match='token' mode='col'>
		<xsl:element name='col{position()}'>
			<xsl:value-of select='.' />
		</xsl:element>
	</xsl:template>

</xsl:stylesheet>